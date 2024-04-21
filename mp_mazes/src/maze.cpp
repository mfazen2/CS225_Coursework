/* Your code here! */
#include "maze.h"
#include <queue>
#include <stack>
SquareMaze::SquareMaze(){
    width_ = 0;
    height_ = 0;
    area_ = 0;
}

/**
 * Makes a new SquareMaze of the given height and width.
 *
 * If this object already represents a maze it will clear all the
 * existing data before doing so. You will start with a square grid (like
 * graph paper) with the specified height and width. You will select
 * random walls to delete without creating a cycle, until there are no
 * more walls that could be deleted without creating a cycle. Do not
 * delete walls on the perimeter of the grid.
 *
 * Hints: You only need to store 2 bits per square: the "down" and
 * "right" walls. The finished maze is always a tree of corridors.)
 *
 * @param width The width of the SquareMaze (number of cells)
 * @param height The height of the SquareMaze (number of cells)
 */
void SquareMaze::makeMaze(int width, int height){
    width_ = width;
    height_ = height;
    area_ = width*height;
    //creates a new set for each cell in the maze
    sets.addelements(area_);
    for(int i = 0; i < area_; ++i){
        right_downWalls.push_back(std::pair<bool,bool>(true,true));
    }
    //need to then merge each set to create a unified up-tree
    while(sets.size(0) != area_){
        //choose random location to delete walls
        int x = rand()%width;
        int y = rand()%height;
        //choose random chance to delete rightwall, otherwise delete downwall
        bool right = rand()%2;
        int coord = x+y*width;
        int rightCoord = (x+1)+y*width;
        int downCoord = x+(y+1)*width;
        if (right){
            if (x <width-1 && right_downWalls[coord].first){
                if (sets.find(coord) != sets.find(rightCoord)){
                    setWall(x,y,0,false);
                    sets.setunion(coord,rightCoord);
                }
            }
        } else {
            if (y < height-1 && right_downWalls[coord].second){
                if (sets.find(coord) != sets.find(downCoord)){
                    setWall(x,y,1,false);
                    sets.setunion(coord,downCoord);
                }
            }  
        }
    }
    
}

/**
 * This uses your representation of the maze to determine whether it is
 * possible to travel in the given direction from the square at
 * coordinates (x,y).
 *
 * For example, after makeMaze(2,2), the possible input coordinates will
 * be (0,0), (0,1), (1,0), and (1,1).
 *
 * - dir = 0 represents a rightward step (+1 to the x coordinate)
 * - dir = 1 represents a downward step (+1 to the y coordinate)
 * - dir = 2 represents a leftward step (-1 to the x coordinate)
 * - dir = 3 represents an upward step (-1 to the y coordinate)
 *
 * You can not step off of the maze or through a wall.
 *
 * This function will be very helpful in solving the maze. It will also
 * be used by the grading program to verify that your maze is a tree that
 * occupies the whole grid, and to verify your maze solution. So make
 * sure that this function works!
 *
 * @param x The x coordinate of the current cell
 * @param y The y coordinate of the current cell
 * @param dir The desired direction to move from the current cell
 * @return whether you can travel in the specified direction
 */
bool SquareMaze::canTravel(int x, int y, int dir) const{
    switch (dir){
        case 0:
            if (x < width_ - 1 && !right_downWalls[x+y*width_].first){
                return true;
            }
            break;
        case 1:
            if (y < height_ - 1 && !right_downWalls[x+y*width_].second){
                return true;
            }
            break;
        case 2:
            if (x > 0 && !right_downWalls[(x-1)+y*width_].first ){
                return true;
            }
            break;
        case 3:
            if (y > 0 &&!right_downWalls[x+(y-1)*width_].second ){
                return true;
            }
            break;
        }
    return false;
}

/**
 * Sets whether or not the specified wall exists.
 *
 * This function should be fast (constant time). You can assume that in
 * grading we will not make your maze a non-tree and then call one of the
 * other member functions. setWall should not prevent cycles from
 * occurring, but should simply set a wall to be present or not present.
 * Our tests will call setWall to copy a specific maze into your
 * implementation.
 *
 * @param x The x coordinate of the current cell
 * @param y The y coordinate of the current cell
 * @param dir Either 0 (right) or 1 (down), which specifies which wall to
 * set (same as the encoding explained in canTravel). You only need to
 * support setting the bottom and right walls of every square in the grid.
 * @param exists true if setting the wall to exist, false otherwise
 */
void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if (dir == 0){
        right_downWalls[x+y*width_].first = exists;
    }
    if (dir == 1){
        right_downWalls[x+y*width_].second = exists;
    }
   
   
}

/**
 * Solves this SquareMaze.
 *
 * For each square on the bottom row (maximum y coordinate), there is a
 * distance from the origin (i.e. the top-left cell), which is defined as
 * the length (measured as a number of steps) of the only path through
 * the maze from the origin to that square.
 *
 * Select the square in the bottom row with the largest distance from the
 * origin as the destination of the maze. solveMaze() returns the
 * winning path from the origin to the destination as a vector of
 * integers, where each integer represents the direction of a step, using
 * the same encoding as in canTravel().
 *
 * If multiple paths of maximum length exist, use the one with the
 * destination cell that has the smallest x value.
 *
 * Hint: this function should run in time linear in the number of cells
 * in the maze.
 *
 * @return a vector of directions taken to solve the maze
 */
std::vector<int> SquareMaze::solveMaze(){
    std::vector<int> path;
    std::queue<int> q;
    std::vector<bool> visited = std::vector<bool>(area_);
    std::vector<int> lastvisited = std::vector<int>(area_);
    std::vector<int> length = std::vector<int>(area_,-1);
    q.push(0);
    visited[0] = true;
    while (!q.empty()){
        int cur = q.front();
        int x = cur%width_;
        int y = cur/width_;
        q.pop();
        if (canTravel(x,y,0) && !visited[cur+1] && length[cur+1] == -1){
            length[cur+1] = length[cur]+1;
            lastvisited[cur+1] = cur;
            visited[cur+1] = true;
            q.push(cur+1);
        }
        if (canTravel(x,y,1) && !visited[cur+width_] && length[cur+width_] == -1){
            length[cur+width_] = length[cur]+1;
            lastvisited[cur+width_] = cur;
            visited[cur+width_] = true;
            q.push(cur+width_);
        }
        if (canTravel(x,y,2) && !visited[cur-1] && length[cur-1] == -1){
            length[cur-1] = length[cur]+1;
            lastvisited[cur-1] = cur;
            visited[cur-1] = true;
            q.push(cur-1);
        }
        if (canTravel(x,y,3) && !visited[cur-width_] && length[cur-width_] == -1){
            length[cur-width_] = length[cur]+1;
            lastvisited[cur-width_] = cur;
            visited[cur-width_] = true;
            q.push(cur-width_);
        }
    }
    int longest = 0;
    int idx;
    for (int i = area_ - width_;i < area_;i++){
        if(length[i] > longest){
            longest = length[i];
            idx = i;
        }
    }
    std::stack<int> directions;
    while (idx){
        if(lastvisited[idx] == idx -1){
            directions.push(0);
        } else if(lastvisited[idx] == idx - width_){
            directions.push(1);
        } else if(lastvisited[idx] == idx +1){
            directions.push(2);
        } else if(lastvisited[idx] == idx + width_){
            directions.push(3);
        }
        idx = lastvisited[idx];
    }
    while (!directions.empty()){
        path.push_back(directions.top());
        directions.pop();
    }
    return path;
}

/**
 * Draws the maze without the solution.
 *
 * First, create a new PNG. Set the dimensions of the PNG to
 * (width*10+1,height*10+1). where height and width were the arguments to
 * makeMaze. Blacken the entire topmost row and leftmost column of
 * pixels, except the entrance (1,0) through (9,0).  For each square in
 * the maze, call its maze coordinates (x,y). If the right wall exists,
 * then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from
 * 0 to 10. If the bottom wall exists, then blacken the pixels with
 * coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
 *
 * The resulting PNG will look like the sample image, except there will
 * be no exit from the maze and the red line will be missing.
 *
 * @return a PNG of the unsolved SquareMaze
 */
cs225::PNG* SquareMaze::drawMaze() const{
    cs225::PNG* temp = new cs225::PNG(width_*10+1,height_*10+1);
    for (int x = 0; x < width_*10+1;x++){
        for (int y = 0; y <height_*10+1;y++){
            if (x==0){
                temp->getPixel(x,y).l = 0;
            }
            if (x > 9 && y == 0){
                temp->getPixel(x,y).l = 0;
            }
        }
    }
    for (int x = 0; x < width_;x++){
        for (int y = 0; y < height_;y++){
            if (right_downWalls[x+y*width_].first){
                //use 11 to correct for 10+1
                for(int k = 0; k < 11;k++){
                    temp->getPixel((x+1)*10,y*10+k).l=0;
                }
            }
            if (right_downWalls[x+y*width_].second){
                //use 11 to correct for 10+1
                for(int k = 0; k < 11;k++){
                    temp->getPixel(x*10 +k,(y+1)*10).l=0;
                }
            }
        }
    }
    return temp;
}

/**
 * This function calls drawMaze, then solveMaze; it modifies the PNG
 * from drawMaze to show the solution vector and the exit.
 *
 * Start at pixel (5,5). Each direction in the solution vector
 * corresponds to a trail of 11 red pixels in the given direction. If the
 * first step is downward, color pixels (5,5) through (5,15) red. (Red is
 * 0,1,0.5,1 in HSLA). Then if the second step is right, color pixels (5,15)
 * through (15,15) red. Then if the third step is up, color pixels
 * (15,15) through (15,5) red. Continue in this manner until you get to
 * the end of the solution vector, so that your output looks analogous
 * the above picture.
 *
 * Make the exit by undoing the bottom wall of the destination square:
 * call the destination maze coordinates (x,y), and whiten the pixels
 * with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
 *
 * @return a PNG of the solved SquareMaze
 */
cs225::PNG* SquareMaze::drawMazeWithSolution(){
    cs225::PNG* temp = drawMaze();
    std::vector<int> path = solveMaze();
    int x = 5;
    int y = 5;
    for (int i = 0; i < static_cast<int>(path.size());i++){
        if (path[i] == 0){
            for (int k = 0; k < 11;k++){
                cs225::HSLAPixel & pix = temp->getPixel(x+k,y);
                pix.h = 0;
                pix.s = 1;
                pix.l = .5;
                pix.a = 1;
            }
            x+=10;
        }else if (path[i] == 1){
            for (int k = 0; k < 11;k++){
                cs225::HSLAPixel & pix = temp->getPixel(x,y+k);
                pix.h = 0;
                pix.s = 1;
                pix.l = .5;
                pix.a = 1;
            }
            y+=10;
        } else if (path[i] == 2){
            for (int k = 0; k < 11;k++){
                cs225::HSLAPixel & pix = temp->getPixel(x-k,y);
                pix.h = 0;
                pix.s = 1;
                pix.l = .5;
                pix.a = 1;
            }
            x-=10;
        }else if (path[i] == 3){
            for (int k = 0; k < 11;k++){
                cs225::HSLAPixel & pix = temp->getPixel(x,y-k);
                pix.h = 0;
                pix.s = 1;
                pix.l = .5;
                pix.a = 1;
            }
            y-=10;
        }
    }
    for (int i = x - 4; i < x+5;i++){
        cs225::HSLAPixel & pix = temp->getPixel(i,y+5);
                pix.l = 1;
                pix.a = 1;
    }
    return temp;
}
