class CfgPatches
{
	class FalconTools
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={};
	};
};

class CfgMods
{
	class FalconTools
	{
	    dir = "FalconTools";
	    picture = "";
	    action = "";
	    hideName = 1;
	    hidePicture = 1;
	    name = "FalconTools";
	    credits = "";
	    author = "";
	    authorID = "0";
	    version = "0.1";
	    extra = 0;
	    type = "mod";

	    dependencies[] = {"Mission"};

		class defs
		{
			class missionScriptModule
			{
				value = "";
				files[] = {"FalconTools/scripts/5_Mission"};
			};
		};
	};
};
