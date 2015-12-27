namespace ExampleAIModuleFSharp

open System.Drawing

open BroodWar
open BroodWar.Api
open BroodWar.Api.Enum

type ExampleAiModuleFSharp() =
    inherit AiBase() 
    [<DefaultValue>] val mutable _ShowBullets : bool
    [<DefaultValue>] val mutable _ShowVisibilityData : bool

    let sendToMinerals (worker:Unit) =
        let minerals = Game.Minerals
        if minerals.Count > 0 then
            let closestMineral = Game.Minerals |> Seq.minBy worker.Distance
            worker.RightClick(closestMineral, false) |> ignore
    let trainWorker (depot:Unit) =
        let trainNonZergWorker (depot:Unit) =
            depot.Train Game.Self.Race.Worker.Type |> ignore
        let trainZergDrone (depot:Unit) =
            let larvae = depot.Larva
            if larvae.Count > 0 then
                (larvae |> Seq.head).Morph(BroodWar.Api.Enum.UnitType.Zerg_Drone) |> ignore

        if depot.UnitType.Race.Type <> RaceType.Zerg then trainNonZergWorker depot
        //if we are Zerg, we need to select a larva and morph it into a drone
        else trainZergDrone depot

    override ai.OnStart () =
        Game.SendText("Hello World!")
        Game.Write("The map is {0}, a {1} player map", Game.MapName, Game.StartLocations.Count)

        // Enable some cheat flags
        Game.EnableFlag Flag.UserInput

        // Uncomment to enable complete map information
        Game.EnableFlag Flag.CompleteMapInformation

        if Game.IsReplay then
            Game.Write "The following players are in this replay:"
            Game.Players |> Seq.filter (fun player -> player.Units.Count > 0 && not player.IsNeutral) |>
                Seq.iter (fun player -> Game.Write("{0}, playing as {1}", player.Name, player.Race.Type))
        else
            Game.Write("The match up is {0} v {1}", Game.Self.Race.Type, Game.Enemy.Race.Type)

            let makeResources (unit:Unit) =
                //send each worker to the mineral field that is closest to it
                if unit.UnitType.IsWorker then sendToMinerals unit
                //if this is a center, tell it to build the appropiate type of worker
                elif unit.UnitType.IsResourceDepot then trainWorker unit
            Game.Self.Units |> Seq.iter makeResources

    override ai.OnEnd (isWinner:bool) =
        //log win to file
        if isWinner then ()
        else ()

    override ai.OnFrame () =
        if ai._ShowVisibilityData then ai.DrawVisibilityData ()
        if ai._ShowBullets then ai.DrawBullets ()

        if not Game.IsReplay then
            let workerType = Game.Self.Race.Worker
            let price = workerType.Price
            let depotOpt = Game.Self.Units |> Seq.tryFind (fun u -> u.UnitType.IsResourceDepot)
            //if our depot queue is empty and we have enouth supply and less than 16 workers
            match depotOpt with
            | Some depot ->
                if depot.TrainingQueue.Count = 0
                && Game.Self.SupplyTotal() - Game.Self.SupplyUsed() >= price.Supply
                && Game.Self.Units |> Seq.filter (fun (u:Unit) -> u.UnitType = workerType) |> Seq.length < 16 then
                    trainWorker depot
            | None -> ()

            ai.DrawStats ()

    override ai.OnSendText(text:string) =
        match text with
        | "/show bullets" -> ai._ShowBullets <- not ai._ShowBullets
        | "/show players" -> ai.ShowPlayers()
        | "/show forces" -> ai.ShowForces()
        | "/show visibility" -> ai._ShowVisibilityData <- not ai._ShowVisibilityData
        | _ ->
            Game.Write("You typed '{0}'!", text)
            Game.SendText text

    override ai.OnReceiveText(player:Player, text:string) =
        Game.Write("{0} said '{1}'", player.Name, text)

    override ai.OnPlayerLeft(player:Player) =
        Game.SendText("{0} left the game.", player.Name)

    override ai.OnNukeDetect(target:Position) =
        if not target.IsUnknown then
            Game.Write("Nuclear Launch Detected at ({0},{1})", target.X, target.Y)
        else
            Game.Write("Nuclear Launch Detected")

    override ai.OnUnitDiscover(unit:Unit) =
        if not Game.IsReplay && Game.FrameCount > 1 then
            Game.SendText("A {0} [{1}] has been discovered at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X, unit.Position.Y)

    override ai.OnUnitEvade(unit:Unit) =
        if not Game.IsReplay && Game.FrameCount > 1 then
            Game.SendText("A {0} [{1}] was left accessible at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X, unit.Position.Y)

    override ai.OnUnitShow(unit:Unit) =
        if not Game.IsReplay && Game.FrameCount > 1 then
            Game.SendText("A {0} [{1}] has been spotted at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X, unit.Position.Y)

    override ai.OnUnitHide(unit:Unit) =
        if not Game.IsReplay && Game.FrameCount > 1 then
            Game.SendText("A {0} [{1}] was last seen at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X, unit.Position.Y)

    override ai.OnUnitCreate(unit:Unit) =
        if Game.FrameCount > 1 then
            if not Game.IsReplay then
                Game.SendText("A {0} [{1}] has been created at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X, unit.Position.Y)
            else
                //if we are in a replay, then we will print out the build order (just of the buildings, not the units).
                if unit.UnitType.IsBuilding && not unit.Player.IsNeutral then
                    let seconds = Game.FrameCount / 24
                    let minutes = seconds / 60
                    let seconds = seconds % 60
                    Game.SendText("{0:2}:{1:2}: {3} creates a {4}", minutes, seconds, unit.Player.Name, unit.UnitType.Type)

    override ai.OnUnitDestroy(unit:Unit) =
        if not Game.IsReplay && Game.FrameCount > 1 then
            Game.SendText("A {0} [{1}] has been destroyed at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X, unit.Position.Y)

    override ai.OnUnitMorph(unit:Unit) =
        if not Game.IsReplay then
            Game.SendText("A {0} [{1}] has been morphed at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X, unit.Position.Y)
        else
            //if we are in a replay, then we will print out the build order (just of the buildings, not the units).
            if unit.UnitType.IsBuilding && not unit.Player.IsNeutral then
                let seconds = Game.FrameCount / 24
                let minutes = seconds / 60
                let seconds = seconds % 60
                Game.SendText("{0:2}:{1:2}: {3} morphs a {4}", minutes, seconds, unit.Player.Name, unit.UnitType.Type)

    override ai.OnUnitRenegade(unit:Unit) =
        if not Game.IsReplay then
            Game.SendText("A {0} [{1}] is now owned by {2}", unit.UnitType.Type, unit, unit.Player.Name)

    override ai.OnSaveGame(gameName:string) =
        Game.Write("The game was saved to \"{0}\".", gameName)

    override ai.OnUnitComplete(unit:Unit) =
        if not Game.IsReplay && Game.FrameCount > 1 then
            Game.SendText("A {0} [{1}] has been completed at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X, unit.Position.Y)
            if unit.Player.Id = Game.Self.Id && unit.UnitType.IsWorker then
                sendToMinerals unit

    member ai.DrawStats () =
        let myUnits = Game.Self.Units
        Game.DrawTextScreen(5, 0, "I have {0} units:", myUnits.Count)
        let groups = myUnits |> Seq.countBy (fun (u:Unit) -> u.UnitType)
        groups |> Seq.iteri (fun line (unitType, number) -> Game.DrawTextScreen(5, 16 * (line + 1), "{0} {1}s", number, unitType.Type))

    member ai.DrawBullets () =
        let drawBullet (bullet:Bullet) =
            let position = bullet.Position
            let velocityX = int bullet.VelocityX
            let velocityY = int bullet.VelocityY
            if bullet.Player = Game.Self then
                Game.DrawLineMap(position.X, position.Y, (position.X + velocityX), (position.Y + velocityY), Color.Green)
                Game.DrawTextMap(position.X, position.Y, "{0}", bullet.Type)
            else
                Game.DrawLineMap(position.X, position.Y, (int) (position.X + velocityX), (int) (position.Y + velocityY), Color.Red)
                Game.DrawTextMap(position.X, position.Y, "{0}", bullet.Type)

        Game.Bullets |> Seq.iter drawBullet

    member ai.DrawVisibilityData () =
        let colorOf x y =
            if Game.IsExplored(x, y) then
                if Game.IsVisible(x, y) then Color.Green else Color.Blue
            else
                Color.Red

        for x = 0 to Game.MapWidth do
            for y = 0 to Game.MapWidth do
                Game.DrawDotMap(x * 32 + 16, y * 32 + 16, colorOf x y);

    member ai.ShowPlayers () =
        let showPlayer (player:Player) = Game.Write("Player [{0}]: {1} is in force: {2}", player.Id, player.Name, player.Force.Name)
        Seq.iter showPlayer Game.Players

    member ai.ShowForces () =
        let showPlayer (player:Player) = Game.Write("  - Player [{0}]: {1}", player.Id, player.Name)
        let showForce (force:Force) =
            Game.Write("Force {0} has the following players:", force.Name)
            Seq.iter showPlayer force.Players
        Seq.iter showForce Game.Forces
