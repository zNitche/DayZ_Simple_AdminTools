class FalconUtils 
{
	static PlayerBase GetPlayer(string name, array<Man> players) {
		
		foreach(Man p : players) {
            if(p.GetIdentity().GetName() == name) {
				return PlayerBase.Cast(p);
			}
		}
		return NULL;
    }	
	
	static bool IsPlayerAnAdmin(PlayerBase player) {
        map<string, string> adminGuids = new map<string, string>();
		
		if (FileExist("$profile:admins.json")) {
			
			JsonFileLoader<map<string, string>>.JsonLoadFile("$profile:admins.json", adminGuids);
					
			foreach (string guid : adminGuids) {
				if (guid == player.GetIdentity().GetId()) {
					return true;
				}
			}
			return false;
		}
		else {
			FalconUtils.logAction(player, "", "filemissing");
			return false;
		}
    }
	
	static string getCmdPrefix() {
		return "!";
	}
	
	static void logAction(PlayerBase player, string command, string type) {
		switch(type) {
			case "filemissing": {
				GetGame().AdminLog("[FalconTools] Can't find admins list. File missing");
				break;
			}
			case "unauthorized": {
				GetGame().AdminLog("[FalconTools] (" + type + " ) " + player.GetIdentity().GetName() + " (" +player.GetIdentity().GetPlainId()+ ", "+player.GetIdentity().GetId() + ") tried to execute admin command"); 
				break;
			}
			
			case "authorized": {
				GetGame().AdminLog("[FalconTools] (" + type + " ) " + player.GetIdentity().GetName() + " (" +player.GetIdentity().GetPlainId()+ ", "+player.GetIdentity().GetId() + ") executed " + command); 	
				break;
			}
			
			default: {
				GetGame().AdminLog("[FalconTools] (" + type + " ) " + player.GetIdentity().GetName() + " (" +player.GetIdentity().GetPlainId()+ ", "+player.GetIdentity().GetId() + ") default log"); 
			}
		}
	}

	
}