#pragma unmanaged

#include <BWAPI.h>

#pragma managed

#include "AiBase.h"

namespace BroodWar
{
	void AiBase::OnStart() { }

	void AiBase::OnEnd(bool isWinner) { }

	void AiBase::OnFrame() { }

	void AiBase::OnSendText(String^ text) { }

	void AiBase::OnReceiveText(Api::Player^ player, String^ text) { }
	
	void AiBase::OnPlayerLeft(Api::Player^ player) { }

	void AiBase::OnNukeDetect(Api::Position^ target) { }

	void AiBase::OnUnitDiscover(Api::Unit^ unit) { }

	void AiBase::OnUnitEvade(Api::Unit^ unit) { }

	void AiBase::OnUnitShow(Api::Unit^ unit) { }

	void AiBase::OnUnitHide(Api::Unit^ unit) { }

	void AiBase::OnUnitCreate(Api::Unit^ unit) { }

	void AiBase::OnUnitDestroy(Api::Unit^ unit) { }

	void AiBase::OnUnitMorph(Api::Unit^ unit) { }

	void AiBase::OnUnitRenegade(Api::Unit^ unit) { }

	void AiBase::OnSaveGame(String^ gameName) { }

	void AiBase::OnUnitComplete(Api::Unit^ unit) { }

	void AiBase::OnPlayerDropped(Api::Player^ player) { }
}
