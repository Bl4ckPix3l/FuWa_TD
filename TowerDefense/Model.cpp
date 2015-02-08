#include "Model.h"

Model::Model(){
	pSQLite = new SQLiteDB();

	//Connect TO database
	if (!pSQLite->OpenConnection("database.db", ""))
	{
		std::cout << "\nConnecting To DB Failed :" << pSQLite->GetLastError().c_str();
	}
}

std::vector<std::map<std::string, std::string>*> Model::execute(char *query){
	
	std::vector<std::map<std::string, std::string>*> entrys;
	int count = 0;
	//Get Data From DB
	IResult *res = pSQLite->ExcuteSelect(query);
	if (!res)
		std::cout << "\n Error:" << pSQLite->GetLastError().c_str();

	else
	{
		//Get Column Count
		int i = res->GetColumnCount();
		
		while (res->Next())
		{
			std::map < std::string, std::string >* map = new std::map<std::string, std::string>();
			
			for (int k = 0; k < i; k++){
				map->insert(std::make_pair(res->NextColomnName(k), res->ColomnData(k)));
				//map->insert(res->ColomnData(k), res->ColomnData(k));
			}
				
			entrys.push_back(map);
			count++;
		}
		return entrys;
		//release Result Data
		//res->Release();
	}
}

std::vector<std::map<std::string, std::string>*> Model::getWaves(){
	return execute("Select * from welle JOIN gegner ON ID = enemy");
};

std::vector<std::map<std::string, std::string>*> Model::getEnemys(){
	return execute("Select * from gegner");
};

std::vector<std::map<std::string, std::string>*> Model::getTowers(){
	return execute("Select * from turm");
};

std::vector<std::map<std::string, std::string>*> Model::getMaps(){
	return execute("Select * from map");
};

std::vector<std::map<std::string, std::string>*> Model::getRace(){
	return execute("Select * from volk");
};