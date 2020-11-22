class FalconTools 
{
	private PlayerBase player;
	private PlayerBase target_player;
	ref array<Man> players = new array<Man>;
	//private bool freecam = false;
	
		
	void FalconTools(PlayerBase player) {
		this.player = player;
	}
	
	PlayerBase getPlayer() {
		return player;
	}
 
    void sendMessageToPlayer(PlayerBase p, string message) {
        Param1<string> param = new Param1<string>( message );
        GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, param, true, p.GetIdentity());
    }
	
	void sendGlobalMessage(string message) {
		GetGame().GetPlayers(players);
		
		foreach (Man player : players) {
			if( player )
				sendMessageToPlayer(PlayerBase.Cast(player), "[Server Message] " + message);
		}
	}
	
	/*void setPlayer(PlayerBase player) {
		this.player = player;
	}
	
	bool isFreeCamActive() {
		return freecam;
	}
	
	
	void setFreecam(bool mode) {
		freecam = mode;
	}*/
	
	///Commands Start
	
	void executeCommand(string command, TStringArray tokens, string message) {
		
		int count = tokens.Count();
		
		switch(command) {
            case "spawn": {
                if(count != 2) { 
					sendMessageToPlayer(player, "failed to spawn an item"); 
					return; 
				}
				
                GetGame().CreateObject(tokens[1], player.GetPosition(), false, true );
                break;
            }
			
			case "test": {
				//sendMessageToPlayer(player, "Server Player: " + getPlayer());
				//sendMessageToPlayer(player, "Client Player: " + getPlayer());
				break;
			}
			
			case "gm": {
				if (count != 2) {
					return;
				}
				
				switch(tokens[1]) {
					case "on": {
						player.SetAllowDamage(false);
						sendMessageToPlayer(player, "gm on"); 
						break;
					}
					case "off": {
						player.SetAllowDamage(true);
						sendMessageToPlayer(player, "gm off"); 
						break;
					}
					default: {
						return;
					}
				}
				break;
			}
			
			//Temporary not working
			/*case "inv": {
				if (count != 2) {
					
					switch(tokens[1]) {
						
						case "on": {
							player.ClearFlags(EntityFlags.VISIBLE|EntityFlags.SOLID, true );
							sendMessageToPlayer(player, "inv on"); 
							break;
						}
							
						case "off": {
							player.SetFlags(EntityFlags.VISIBLE|EntityFlags.SOLID, true);
							sendMessageToPlayer(player, "inv off"); 
							break;
						}
							
						default: {
							return;
						}
						break;
					}
			  	}					
			}*/

			case "kys": {
				player.SetHealth(0);
				break;
			}
					
			case "kill": {
				if(count != 2) { 
					return; 
				}
				GetGame().GetPlayers(players);
				
                target_player = FalconUtils.GetPlayer(tokens[1], players);
                if(target_player == NULL) {
					sendMessageToPlayer(player, "Cant find player " + target_player);
					return;
                } else {
                    target_player.SetHealth(0);
                }
                break;
			}
			
			case "pos": {
				sendMessageToPlayer(player, player.GetPosition().ToString());
				break;
			}
			
			case "toall": {
				if (count != 2) {
					return;
				}
				
				sendGlobalMessage(tokens[1]);
				
				break;
			}
			
			case "goto": {
				
                if(count != 2) {
					return; 
				}
				
				GetGame().GetPlayers(players);
				
                target_player = FalconUtils.GetPlayer(tokens[1], players);
                if(target_player == NULL) {
					sendMessageToPlayer(player, "Cant find player " + target_player);
					return;
                } else {
                    player.SetPosition(target_player.GetPosition());
                }
                break;
            }
			
			case "tpto": {
				if(count != 4) { 
					return; 
				}
					string vecto = tokens[1] + " " + tokens[2] + " " + tokens[3];
					vector vec = vecto.ToVector();
				
					player.SetPosition(vec);
				
                break;
			}
			
			case "get": {
				if (count != 2) {
					return;
				}
				
				GetGame().GetPlayers(players);
				
                target_player = FalconUtils.GetPlayer(tokens[1], players);
                if(target_player == NULL) {
					return;
                } else {
                    target_player.SetPosition(player.GetPosition());
                }
                break;
			}
			
			case "settime": {
				
				//!settime [hours] [minutes]
				//it takes a while to apply changes
				
                if(count != 3) {
					return; 
				}
				
				
				int year, month, day, hour, minute;
				GetGame().GetWorld().GetDate(year, month, day, hour, minute);
				
                GetGame().GetWorld().SetDate( year, month, day, tokens[1].ToInt(), tokens[2].ToInt());
				
				sendMessageToPlayer(player, "Time set to " +  tokens[1] + ":" + tokens[2]); 

                break;
            }
			
			case "heal": {
                PlayerBase target;
				
				if (count == 2) {
					GetGame().GetPlayers(players);
					target = FalconUtils.GetPlayer(tokens[1], players);
                    if(target == NULL) {
						sendMessageToPlayer(player, "Cant find player " + tokens[1]);
                        return;
                    } else {
                        healPlayer(target);
                    }
				}
                else if (count == 1) {
					healPlayer(player);
                } 
				else {
                    return;
                }
				
                break;
            }
			
			case "car": {
				spawnCar();
				break;
			}
			
			case "warrior": {
				spawnWarrior();
				break;
			}
			
			case "strip": {
				if (count == 1) {
					player.RemoveAllItems();
				}
				else if (count == 2) {
					GetGame().GetPlayers(players);
					
					target_player = FalconUtils.GetPlayer(tokens[1], players);
					
					if (target_player == NULL) {
						sendMessageToPlayer(player, "Cant find player " + tokens[1]);
						return;
					}
					
					target_player.RemoveAllItems();
				}
				else {
					return;
				}
				
				break;
			}
           
            default: {
                sendMessageToPlayer(player, "Unknown: " + command);
                break;
            }
        }
	}
	
	///Commands End
	
	///CommandsHelpersStart
	void healPlayer(PlayerBase player) {
		player.SetHealth(player.GetMaxHealth("", ""));
        player.SetHealth("", "Blood", player.GetMaxHealth("", "Blood"));
        player.GetStatStamina().Set(1000);
        player.GetStatEnergy().Set(1000);
        player.GetStatWater().Set(1000);
	}
	
	void spawnCar() {		
		Car vehicle;
				
		vehicle = Car.Cast(GetGame().CreateObject("OffroadHatchback", player.GetPosition()));
		vehicle.Fill(CarFluid.FUEL, 1000);
		vehicle.GetInventory().CreateAttachment("HatchbackTrunk");
		vehicle.GetInventory().CreateAttachment("HatchbackHood");
		vehicle.GetInventory().CreateAttachment("HatchbackDoors_CoDriver");
		vehicle.GetInventory().CreateAttachment("HatchbackDoors_Driver");
		vehicle.GetInventory().CreateAttachment("HatchbackWheel");
		vehicle.GetInventory().CreateAttachment("HatchbackWheel");
		vehicle.GetInventory().CreateAttachment("HatchbackWheel");
		vehicle.GetInventory().CreateAttachment("HatchbackWheel");
		vehicle.GetInventory().CreateAttachment("CarBattery");
		vehicle.GetInventory().CreateAttachment("SparkPlug");
		vehicle.GetInventory().CreateAttachment("CarRadiator");
		vehicle.Fill(CarFluid.COOLANT, 1000);
	}
	
	void spawnWarrior() {
		EntityAI weapon = player.GetHumanInventory().CreateInHands("M4A1");
					
		weapon.GetInventory().CreateAttachment("M4_OEBttstck");
		weapon.GetInventory().CreateAttachment("M4_CarryHandleOptic");
		weapon.GetInventory().CreateAttachment("M4_PlasticHndgrd");
		//weapon.GetInventory().CreateAttachment("Mag_STANAG_30Rnd");
					
		player.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
	}
	///CommandsHelpersEnd
	
	///Sandbox

	
	///
}