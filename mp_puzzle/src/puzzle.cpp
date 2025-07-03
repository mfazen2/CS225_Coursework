/**
 * @file puzzle.cpp
 * Implementation of puzzle class.
 */
#include "puzzle.h"



std::ostream& operator<<(std::ostream& os, PuzzleState P){
    auto a = P.asArray();
    for (int i = 0; i < 16; i++){
        os << static_cast<unsigned>(a[i]) <<" ";
        if ( static_cast<unsigned>(a[i]) < 10){
            os << " ";
        } 
        if (i == 3 || i == 7 || i == 11 || i == 15){
            os << std::endl;
        }
    }
    return os;
}

PuzzleState::PuzzleState(){
    for (int i = 0; i < 15;i++){
        pstate[i+1] = i;
    }
    pstate[0] = 15;
}

PuzzleState::PuzzleState(const std::array<uint8_t,16> state){
    for (int i = 0; i < 16;i++){
        if (state[i] > 15 || state[i] < 0){
            *this = FailedPuzzle();
            return;
        }   
        pstate[state[i]] = i;
   }
    
}

PuzzleState PuzzleState::FailedPuzzle() const{
    PuzzleState p;
    p.pstate[0] = 0;
    return p;
}
std::array<uint8_t, 16> PuzzleState::asArray() const{
    std::array<uint8_t,16> r;
    for (auto elem: pstate){
        r[elem.second] = elem.first;
    }
    if (pstate == FailedPuzzle().pstate){
        for(int i = 0; i < 16;i++){
            r[i] = 0;
        }
    }
    return r;
}

bool PuzzleState::operator==(const PuzzleState &rhs) const{
    if (rhs.pstate.size() != pstate.size()){return false;}
    for (int i = 0; i < 16; i++){
        if (pstate.at(i) != rhs.pstate.at(i)){
            return false;
        }
    }
    return true;
}

bool PuzzleState::operator<(const PuzzleState &rhs) const{
    auto lhs = asArray();
    auto r = rhs.asArray();
    if (lhs.size() != r.size()){ return false;}
    for (int i = 0; i < 16; i++){
        if (lhs[i] < r[i]){
            return true;
        }
        if (lhs[i] > r[i]){
            return false;
        }
    }
    return false;
}
bool PuzzleState::operator!=(const PuzzleState &rhs) const{
    return !(*this==rhs);
}

PuzzleState PuzzleState::getNeighbor(Direction direction) const{
    int newindex = 0;
    int emptyindex = pstate.at(0);
    if (direction == Direction::UP){
        newindex = emptyindex + 4;
        if (newindex > 15){ return FailedPuzzle();}
    } else if (direction == Direction::DOWN){
        newindex = emptyindex  - 4;
        if (newindex < 0){ return FailedPuzzle();}
    } else if (direction == Direction::LEFT){
        newindex = emptyindex  + 1;
        if (newindex > 15 || emptyindex == 11 || emptyindex == 7 || emptyindex == 3){ return FailedPuzzle();}
    } else{
        newindex = emptyindex  - 1;
        if (newindex < 0 || emptyindex == 4 || emptyindex == 8 || emptyindex == 12){ return FailedPuzzle();}
    }
    std::array<uint8_t,16> neighbor = asArray();
    std::swap(neighbor[newindex], neighbor[emptyindex]);
    PuzzleState n = PuzzleState(neighbor);
    return n;
}

std::vector<PuzzleState> PuzzleState::getNeighbors() const{
    std::vector<PuzzleState> neighbors;
    std::vector<Direction> directions = {Direction::UP,Direction::DOWN,Direction::LEFT,Direction::RIGHT};
    for (auto d : directions){
        PuzzleState p = getNeighbor(d);
        if (p != FailedPuzzle()){
            neighbors.push_back(p);
        }
    }
    return neighbors;
}



int PuzzleState::manhattanDistance(const PuzzleState desiredState) const{
    int sum = 0;
    for (int i = 1; i < 16; i++){
        int deltax = abs(pstate.at(i)/4 - desiredState.pstate.at(i)/4);
        int deltay = abs(pstate.at(i)%4 - desiredState.pstate.at(i)%4);
        sum+= (deltax+deltay);
    }
    return sum;
}


std::vector<PuzzleState> solveAstar(const PuzzleState &startState, const PuzzleState &desiredState, size_t *iterations) {
    std::vector<PuzzleState> r;
    std::unordered_map<PuzzleState, PuzzleState> prev;
    std::priority_queue<std::pair<int, PuzzleState>, std::vector<std::pair<int, PuzzleState>>, std::greater<>> pq;

    if (startState == desiredState) {
        if (iterations != nullptr) {
            *iterations = 1;
        }
        std::cout << "already solved" << std::endl;
        r.push_back(startState);
        return r;
    }

    int iter = 0;
    pq.push({startState.manhattanDistance(desiredState), startState});
    prev[startState] = startState;
    while (!pq.empty()) {
        iter++;
        PuzzleState cur = pq.top().second;
        pq.pop();
        if (cur == desiredState) {
            break;
        }

        for (auto &neighbor : cur.getNeighbors()) {
            int dist = neighbor.manhattanDistance(desiredState);
            if (prev.find(neighbor) == prev.end() || dist < neighbor.manhattanDistance(prev[neighbor])) {
                pq.push({dist + iter, neighbor});
                prev[neighbor] = cur;
            }
        }
    }

    // Reconstruct the path

    std::stack<PuzzleState> pathstates;
    PuzzleState cur = desiredState;
    while (cur != startState){
        std::cout << "..." << std::endl;
        pathstates.push(cur);
        if (prev.find(cur) == prev.end()){break;}
        cur = prev.at(cur);
    }
    pathstates.push(startState);
    while(!pathstates.empty()){
        r.push_back(pathstates.top());
        pathstates.pop();
    }
    if (iterations != nullptr){
        *iterations = iter;
    }
    return r;
}

std::vector<PuzzleState> solveBFS(const PuzzleState &startState, const PuzzleState &desiredState, size_t *iterations){
    std::vector<PuzzleState> r;
    std::unordered_map<PuzzleState,PuzzleState> prev;
    std::queue<PuzzleState> q;
    std::unordered_set<PuzzleState> visited;

    if(startState == desiredState){
        if (iterations != nullptr){
            *iterations = 1;
        }
        std::cout << "already solved" << std::endl;
        r.push_back(startState);
        return r;
    }


    int iter = 0;
    q.push(startState);
    prev[startState] = startState;
    visited.insert(startState); // Mark startState as visited
    while (!q.empty()) {
        iter++;
        PuzzleState cur = q.front();
        q.pop();
        if (cur == desiredState) {
            break;
        }

        for (auto& neighbor : cur.getNeighbors()) {
            if (visited.find(neighbor) == visited.end()) {
                q.push(neighbor);
                prev[neighbor] = cur;
                visited.insert(neighbor); // Mark neighbor as visited
            }
        }
    }

    // Reconstruct the path
    std::stack<PuzzleState> pathstates;
    PuzzleState cur = desiredState;
    while (cur != startState){
        pathstates.push(cur);
        if (prev.find(cur) == prev.end()){break;}
        cur = prev.at(cur);
    }
    pathstates.push(startState);
    while(!pathstates.empty()){
        r.push_back(pathstates.top());
        pathstates.pop();
    }
    if (iterations != nullptr){
        *iterations = iter;
    }
    return r;
}

