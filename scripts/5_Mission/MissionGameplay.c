//DeveloperFreeCamera throws NULL pointer to instance

modded class MissionGameplay {
		
	//ref FalconTools FT = new FalconTools(PlayerBase.Cast(GetGame().GetPlayer()));
	PlayerBase player;
	bool isFreeCamActive = false;

	override void OnKeyPress( int key )
    {
        super.OnKeyPress( key );
		
		if (key == KeyCode.KC_J) {
			FalconTools FT = new FalconTools(PlayerBase.Cast(GetGame().GetPlayer()));
			
			if (FalconUtils.IsPlayerAnAdmin(FT.getPlayer())) {
				player = GetGame().GetPlayer();
				
				HumanInputController hic = player.GetInputController();
				
				if (hic) {
					
					if (isFreeCamActive) {
						isFreeCamActive = false;
					}
					else {
						isFreeCamActive = true;
					}
					
					hic.SetDisabled(isFreeCamActive);
				}
				DeveloperFreeCamera.FreeCameraToggle(player, false);
			}
		}
    }
}