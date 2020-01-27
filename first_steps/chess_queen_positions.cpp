/*
 * task from hackerrank - https://www.hackerrank.com/challenges/queens-attack-2/problem
 */

#include <iostream>
#include <vector>
#include <boost/range/combine.hpp>

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
			for(auto obstacle : obstacles)
			{
				if(obstacle[0] == pos_h && obstacle[1] == pos_v)
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
	
	for(auto tup : boost::combine(attack_fields, dir))
	{
		
		std::vector<int> attack_dir, d;
	
		boost::tie(attack_dir,d) = tup;

		while(true)
		{
			if(attack_dir[2] < 0)
			{
				break;
			}

			if(!check_position(attack_dir[0] + d[0], attack_dir[1] + d[1], obstacles, n))
			{
				attack_dir[2] = -1;
				break;
			}
			
			attack_dir[0] += d[0];
			attack_dir[1] += d[1];

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

	vector_2d obstacles{{5, 5}, {4,2}, {2,3}, {3,2}};
	
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

