modded class MissionServer
{ 	
    override void OnEvent(EventType eventTypeId, Param params)  
   
    {
        super.OnEvent(eventTypeId,params);
		
		
        if(eventTypeId != ChatMessageEventTypeID) {
			return;
		}
		
        ChatMessageEventParams chat_params = ChatMessageEventParams.Cast( params );
		
        if(chat_params.param1 != 0 || chat_params.param2 == "") {
			return;
		}
		
		string cmdPrefix = FalconUtils.getCmdPrefix();
		
        string message = chat_params.param3, prefix, param0, command;
		
        TStringArray tokens = new TStringArray;
		message.Split(" ", tokens);
		
        param0 = tokens.Get(0);
        param0.ParseStringEx(prefix); 
		
		if(prefix != cmdPrefix) {
			//Idk if it is needed or not
			//super.OnEvent(eventTypeId, params);
			//
			//super.OnEvent(eventTypeId,params);
			return;
		}
		
		PlayerBase player; 
			
        array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);
		
        param0.ParseStringEx(command);
		
		player = FalconUtils.GetPlayer(chat_params.param2, players);
		
        if(!player) {
			return;
		}
		
		FalconTools AdminTools = new FalconTools(player);
		
		if(!FalconUtils.IsPlayerAnAdmin(player)) { 
			FalconUtils.logAction(AdminTools.getPlayer(), "", "unauthorized");
			return;
		}
		
       	FalconUtils.logAction(AdminTools.getPlayer(), command, "authorized");
       
		//Print("PLayer => " + AdminTools.getPlayer());
		AdminTools.executeCommand(command, tokens, message);
		
		delete AdminTools;
    }

}