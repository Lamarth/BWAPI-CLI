class TournamentModule : public BWAPI::TournamentModule
{
	virtual bool onAction(int actionType, void* parameter = NULL);
	virtual void onFirstAdvertisement();
};
