#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> cup_record,path,cup_status;
vector<int> cup_capicity , temporary_container1 , temporary_container2 , temporary_container3 , temporary_container4;
queue<vector<int>> cup_status_node;
bool check;
int cup_number , volume_record , target_water_volume , great_common_factor , step_pos ,pos_check, the_largest_water_volume = 0;
int i , j , x;



void path_display(){
	for(unsigned int y = path.size()-1 ; y >= 0 ; y--){
		for(x = 0 ; x < step_pos+1 ; x++){
			cout << path[y][x] << " ";
		}
		cout << "\n";
	}
	return;
}


bool CheckWaterVolume(){
	for(x = 0 ; x < cup_number ; x++){
		if(temporary_container1[x] == target_water_volume){
			cout << temporary_container1[step_pos] << "\n";
			return true;
		}
	}
	return false;
}



void write(){
	for(x = 0 ; x < cup_number ; x++){
		temporary_container3[x] = temporary_container1[x];
	}
	return;
}

void end(){
	pos_check = 0;
	path.push_back(temporary_container1);
	for(x = 0 ; x < cup_number ; x++){
		temporary_container3[x] = temporary_container1[x] - temporary_container1[x+cup_number];
		pos_check += temporary_container3[x];
	}
	if(pos_check == 0){
		path_display();
		return;
	}
	for(unsigned int k = 0 ; k < cup_status.size() ; k++){
		for(x = 0 ; x < step_pos+1 ; x++){
			// cout << cup_status[k][i]<<" ";
			temporary_container4[x] = cup_status[k][x];
		}
		if(temporary_container3 == temporary_container4){
			temporary_container1 = cup_status[k];
			end();
			return;
		}
	}
	return;
}



void test(){
	check = true;
	for(unsigned int k = 0; k < cup_record.size();k++){
		if(temporary_container3 == cup_record[k]){
			goto place;
		}
	}
	for(x = 0 ; x < cup_number ; x++){
		temporary_container1[cup_number + x] = temporary_container1[x] - temporary_container2[x];
	}
	cup_record.push_back(temporary_container3);
	cup_status_node.push(temporary_container1);
	place:
	return;
}

int main(){
	cin >> cup_number;
	for(i = 0 ; i < cup_number ; i++){
		cin >> volume_record;
		cup_capicity.push_back(volume_record);
		the_largest_water_volume = max(the_largest_water_volume , cup_capicity[i]);
	}
	cin >> target_water_volume;
	great_common_factor = cup_capicity[0];
	step_pos = cup_number * 2 ;
	for(i = 0 ; i < cup_number ; i++){
		great_common_factor = __gcd(great_common_factor , cup_capicity[i]);
		temporary_container3.push_back(0);
		temporary_container4.push_back(0);
	}
	if(target_water_volume % great_common_factor != 0 || target_water_volume > the_largest_water_volume){
		cout <<-1 ;
		return 0 ; 
	}
	else{
		for(i = 0 ; i< step_pos+1 ; i++){
			temporary_container1.push_back(0);
		}
	}
	cup_status.push_back(temporary_container1);
	cup_status_node.push(temporary_container1);
	cup_record.push_back(temporary_container3);
	while(! cup_status_node.empty()){
		temporary_container1 = cup_status_node.front();
		temporary_container2 = cup_status_node.front();
		
		cup_status.push_back(temporary_container1);
		cup_status_node.pop();
		for(i = 0 ; i < cup_number ; i++){
			if(temporary_container1[i] != 0){
				temporary_container1[i] = 0;
				temporary_container1[step_pos]++;
				write();
				test();
				if(CheckWaterVolume()){
					cup_status.push_back(temporary_container1);
					end();
					return 0;
				}
				temporary_container1 = temporary_container2;
			}
			if(temporary_container1[i] != cup_capicity[i]){
				temporary_container1[i] = cup_capicity[i];
				temporary_container1[step_pos]++;
				write();
				test();
				if(CheckWaterVolume()){
					cup_status.push_back(temporary_container1);
					end();
					return 0;
				}
				temporary_container1 = temporary_container2;
			}
			for(j = 0 ; j < cup_number ; j++){
				if(i == j)continue;
				temporary_container1[i] = max(temporary_container2[i] + temporary_container2[j] - cup_capicity[j] , 0);
				temporary_container1[j] = min(temporary_container2[i] + temporary_container2[j] , cup_capicity[j]);
				temporary_container1[step_pos]++;
				write();
				test();
				if(CheckWaterVolume()){
					cup_status.push_back(temporary_container1);
					end();
					return 0;
				}
				temporary_container1 = temporary_container2;
			}

		}
	}
	cout<<-1;
	return 0;
}

