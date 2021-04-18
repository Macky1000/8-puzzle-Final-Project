#include "puzzle.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <iterator>

void bfs(int initial_state[3][3], int final_state[3][3])
{
  int i = 0;
  int queue []={};
  int visited []={}; 
  queue += find_adjacent();//check find_adjacent function 
  while(true)
  {
    i++;
    int cur_pos;
    cur_pos = queue.pop(0);
     bool exists = find(begin(visited), end(visited), cur_pos) != end(visited);
    if (exists)
    {
        cout << "DUPLICATE";
        //debug_print(cur_pos, i);
        continue;
    }else{
        visited.append(cur_pos[0]);
        cout << "APPEND";
        if(cur_pos[0] == final_state)
        {
            cout << "GOAL";
            //debug_print(current, i);
            cout << "Solution: The shortest path cost = cur_pos[1]";
            break;
        }
    }
    queue += find_adjacent();
    //debug_print(current, i);
  }

}
