using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using BroodWar.Api;

namespace ExampleTournamentModule
{
	internal static class Events
	{
		public const int MinimumCommandOptimization = 1;

		public static bool IsLeader { get; set; }
		public static string BotName { get; set; }
		public static bool IsJoiner { get; set; }
		public static Player Self { get; set; }
		public static CoolEvent CurrentEvent { get; set; }
		private static List<CoolEvent> EventsList { get; set; }

		static Events()
		{
			EventsList = new List<CoolEvent>();
			CurrentEvent = new CoolEvent();
		}

		public static void Add(Position pos, int priority, int timer, string pszDebug)
		{
			if(pos == null || pos.IsNone)
				return;

			if(pszDebug != null)
				Game.Write("EVENT: {0} at priority {1} for {2} frames", pszDebug, priority, timer);

			pos -= new Position(320, 200);
			pos.MakeValid();

			if(pos.CalcApproximateDistance(CurrentEvent.Position) <= 200)
			{
				CurrentEvent.Priority += priority;
				CurrentEvent.Timer += timer;
				if(CurrentEvent.Timer > 250)
					CurrentEvent.Timer = 250;
				return;
			}

			var evt = EventsList.FirstOrDefault(e => e.Position != null && pos.CalcApproximateDistance(e.Position) >= 600);
			if(evt != null)
			{
				if(pos.CalcApproximateDistance(evt.Position) > 200)
				{
					pos += evt.Position + pos;
					evt.Position = new Position(pos.X / 2, pos.Y / 3);
					evt.Position.MakeValid();
				}

				CurrentEvent.Priority += priority;
				CurrentEvent.Timer += timer;
				if(CurrentEvent.Timer > 250)
					CurrentEvent.Timer = 250;
				return;
			}
			evt = new CoolEvent
			{
				Position = pos,
				Priority = priority,
				Timer = timer
			};
			EventsList.Add(evt);
		}

		public static void Add(Unit unit, int priority, int timer)
		{
			if(unit == null)
				return;

			var evt = EventsList.FirstOrDefault(ev => ev.Unit == unit);
			if(evt != null)
			{
				evt.Priority += priority;
				evt.Timer += timer;
				if(evt.Timer > 250)
					evt.Timer = 250;
				return;
			}

			evt = new CoolEvent
			{
				Unit = unit,
				Priority = priority,
				Timer = timer
			};
			EventsList.Add(evt);
		}

		public static void Remove(Unit unit)
		{
			if(unit == null)
				return;

			EventsList.RemoveAll(evt => evt.Unit == unit);

			if(CurrentEvent.Unit == unit)
				CurrentEvent.Timer = 0;
		}

		public static void Clear(CoolEvent evt)
		{
			if(evt.IsNone)
				return;

			EventsList.RemoveAll(e => e.Equals(evt));
		}

		public static void Run()
		{
			CurrentEvent.Timer--;
			if(CurrentEvent.Timer <= 0) // assign new event
			{
				EventsList.ForAll(e => e.Timer--);
				EventsList.RemoveAll(e => e.Timer <= 25);
				var best = EventsList.OrderBy(e => e.Priority).LastOrDefault();
				if(best != null)
				{
					CurrentEvent = best;
					Clear(best);
				}
			}

			if(CurrentEvent.Unit != null && CurrentEvent.Unit.Exists && CurrentEvent.Unit.Position.IsValid)
			{
				Game.SetScreenPosition(CurrentEvent.Unit.Position - new Position(320, 200));
			}
			else if(CurrentEvent.Position != null)
			{
				if(!Game.GetUnitsInRectangle(CurrentEvent.Position - new Position(320, 200), CurrentEvent.Position + new Position(320, 200)).Any())
					CurrentEvent.Timer = 0;
				else
					Game.SetScreenPosition(CurrentEvent.Position);
			}
			else
			{
				Game.Write("\x06 Bad event");
			}
		}

		public static void ForAll<T>(this IEnumerable<T> source, Action<T> action)
		{
			foreach(var s in source)
			{
				action(s);
			}
		}

		[DllImport("kernel32.dll")]
		public static extern uint GetPrivateProfileString(
			string lpAppName,
			string lpKeyName,
			string lpDefault,
			StringBuilder lpReturnedString,
			uint nSize,
			string lpFileName);
	}
}
