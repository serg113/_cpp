#include <iostream>
#include <vector>


typedef std::vector<std::vector<int>> vector_2d;


/* 
 * function checks if obstacle or out of board position occur at next step of attack
 */

bool check_position(int pos_h, int pos_v, const vector_2d obstacles, int n)
{
	bool go_next = true;
	
	if(pos_h > n || pos_h < 1 || pos_v > n || pos_v < 1)
	{
		go_next = false;
	}
	else
	{
		if(obstacles.size() > 0)
		{
			for(auto i = 0; i < obstacles.size(); i++)
			{
				if(obstacles[i][0] == pos_h && obstacles[i][1] == pos_v)
				{
					go_next = false;
					break;
				}
			}
		}
	}

	return go_next;
}

/* 
 * function counts attack squeres according to horizontal and vertical 
 * positions (p_h, p_v) of Queen on nxn chess board 
 * with taking into account obstacles at attacking vectors 
 */
int get_attack_count(int p_h, int p_v, int n, const vector_2d obstacles)
{
	int attack_count = 0;

	vector_2d attack_fields;

	vector_2d dir = {{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};


	for (auto i = 0; i < 8; i++)
	{
		attack_fields.push_back({p_h, p_v, 1}); //last index indicates that obstacle doesnot occur
	}

	for(auto i = 0; i < 8; i++)
	{
		while(true)
		{
			if(attack_fields[i][2] < 0)
			{
				break;
			}

			if(!check_position(attack_fields[i][0] + dir[i][0], attack_fields[i][1] + dir[i][1], obstacles, n))
			{
				attack_fields[i][2] = -1;
				break;
			}
			
			attack_fields[i][0] += dir[i][0];
			attack_fields[i][1] += dir[i][1];

			attack_count++;
		}
	}	
	return attack_count;	
}


int main()
{
	// input
	int n = 5;
	int p_h = 4;
	int p_v = 3;

	vector_2d obstacles{{5, 5}, {4,2}, {2,3}};

	// computation function call
	int attacks = get_attack_count(p_h, p_v, n, obstacles);

	// output
	std::cout << "\n*** input ***\nboard dimensions: " << n << "x" << n << std::endl;
	std::cout << "Queen position: " << p_h << "," << p_v << std::endl;
	
	for(auto v : obstacles)
	{
		std::cout << "obstacle at position: " << v[0] << "," << v[1] << std::endl;
	}

	std::cout << "\n*** output ***\nnumber of Queen's attack positions: " << attacks << std::endl << std::endl;

	return 0;
}
