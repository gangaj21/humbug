#include<bits/stdc++.h>
using namespace std;

vector<vector<bool>> right_barrier, left_barrier, up_barrier, down_barrier;
int min_moves;
map<vector<string>, int> mp;
bool maintain_state = false;

void print_info(){
    cout<<"Considering the below diamond as the playfield, the top point is taken as origin of the coordinates.\n";
    cout<<"X-axis is in \\ direction and Y-axis is in / direction\n";
    int n = 3; 

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            cout << " ";
        }
        for (int k = 0; k < 2 * i + 1; ++k) {
            cout << "*";
        }
        cout << endl;
    }
    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j < n - i - 1; ++j) {
            cout << " ";
        }
        for (int k = 0; k < 2 * i + 1; ++k) {
            cout << "*";
        }
        cout << endl;
    }
    cout<<"\nAccording to the convention described, below is the solution of the level\n\n";
}

vector<string> parseInputFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filePath << endl;
        exit(EXIT_FAILURE);
    }
    file >> min_moves;
    int rows, cols;
    file >> rows >> cols;


    vector<string> gridData;
    string line;
    for(int i=0;i<rows;i++){
        file>>line;
        gridData.push_back(line);
    }
    right_barrier = vector<vector<bool>>(gridData.size(), vector<bool>(gridData[0].size(), false));
    left_barrier = vector<vector<bool>>(gridData.size(), vector<bool>(gridData[0].size(), false));
    up_barrier = vector<vector<bool>>(gridData.size(), vector<bool>(gridData[0].size(), false));
    down_barrier = vector<vector<bool>>(gridData.size(), vector<bool>(gridData[0].size(), false));

    int numbarriers;
    file >> numbarriers;
    while (numbarriers--)
    {
        int r,c;
        string b;
        file>>r>>c>>b;
        if(b == "R") right_barrier[r][c] = true;
        if(b == "L") left_barrier[r][c] = true;
        if(b == "U") up_barrier[r][c] = true;
        if(b == "D") down_barrier[r][c] = true;
    }
    
    file.close();
    return gridData;
}


// R 0 D 1 L 2 U 3
// barrier = 0 if barrier is not present
vector<pair<int,int>> get_snail_moves(vector<string> &matrix, int i, int j){
    int n = matrix.size();
    int m = matrix[0].size();
    vector<pair<int, int>> ans(4, {-1,-1});
    if(j < m-1 && (matrix[i][j+1] == '.' || matrix[i][j+1] == '*') && !right_barrier[i][j]){
        ans[0] = {i,j+1};
    }
    if(i < n-1 && (matrix[i+1][j] == '.' || matrix[i+1][j] == '*') && !down_barrier[i][j]){
        ans[1] = {i+1,j};
    }
    if(j > 0 && (matrix[i][j-1] == '.' || matrix[i][j-1] == '*') && !left_barrier[i][j]){
        ans[2] = {i,j-1};
    }
    if(i > 0 && (matrix[i-1][j] == '.' || matrix[i-1][j] == '*') && !up_barrier[i][j]){
        ans[3] = {i-1,j};
    }
    return ans;
}

vector<pair<int,int>> get_spider_moves(vector<string> &matrix, int i, int j){
    int n = matrix.size();
    int m = matrix[0].size();
    vector<pair<int,int>> ans(4, {-1,-1});
    int r = j+1;
    for(;r<m;r++){
        if(right_barrier[i][r-1]) {r--; ans[0] = {i,r};break;}
        if(matrix[i][r] == 'E') break;
        if(matrix[i][r] != '*' and matrix[i][r] != '.'){
            ans[0] = {i,r-1};
            break;
        }
    }
    if(r == m){
        if(right_barrier[i][r-1]) ans[0] = {i,r-1};
        else ans[0] = {-1,-1};
    }
    

    r = i+1;
    for(;r<n;r++){
        if(down_barrier[r-1][j]) {r--; ans[1] = {r,j};break;}
        if(matrix[r][j] == 'E') break;
        if(matrix[r][j] != '*' and matrix[r][j] != '.'){
            ans[1] = {r-1, j};
            break;
        }
    }
    if(r == n){
        if(down_barrier[r-1][j]) ans[1] = {r-1, j};
        else ans[1] = {-1,-1};
    }


    r = j-1;
    for(;r>=0;r--){
        if(left_barrier[i][r+1]) {r++; ans[2] = {i,r};break;}
        if(matrix[i][r] == 'E') break;
        if(matrix[i][r] != '*' and matrix[i][r] != '.'){
            ans[2] = {i,r+1};
            break;
        }
    }
    if(r == -1){
        if(left_barrier[i][r+1]) ans[2] = {i,r+1};
        else ans[2] = {-1,-1};
    }


    r = i-1;
    for(;r>=0;r--){
        if(up_barrier[r+1][j]) {r++; ans[3] = {r,j};break;}
        if(matrix[r][j] == 'E') break;
        if(matrix[r][j] != '*' and matrix[r][j] != '.'){
            ans[3] = {r+1, j};
            break;
        }
    }
    if(r == -1){
        if(up_barrier[r+1][j]) ans[3] = {r+1, j};
        else ans[3] = {-1,-1};
    }
    for(int ik=0;ik<4;ik++){
        if(ans[ik].first == i and ans[ik].second == j) ans[ik] = {-1,-1};
    }
    return ans;
}

vector<pair<int,int>> get_ladybug_moves(vector<string> &matrix, int i, int j){
    int n = matrix.size();
    int m = matrix[0].size();
    vector<pair<int, int>> ans(4, {-1,-1});
    if(j < m-1 && (matrix[i][j+1] == '.' || matrix[i][j+1] == '*') && !right_barrier[i][j]){
        ans[0] = {i,j+1};
        if(!right_barrier[i][j+1] && j==m-2) {ans[0] = {-1,-1};}
        if(j < m-2 && (matrix[i][j+2] == '.' || matrix[i][j+2] == '*') && !right_barrier[i][j+1]){
            ans[0] = {i,j+2}; 
        }
        if(j < m-2 && matrix[i][j+2] == 'E' && !right_barrier[i][j+1]) {ans[0] = {-1,-1}; }
    }
    if(i < n-1 && (matrix[i+1][j] == '.' || matrix[i+1][j] == '*') && !down_barrier[i][j]){
        ans[1] = {i+1,j};
        if(!down_barrier[i+1][j] && i==n-2) ans[1] = {-1,-1};
        if(i < n-2 && (matrix[i+2][j] == '.' || matrix[i+2][j] == '*') && !down_barrier[i+1][j]){
            ans[1] = {i+2,j};
        }
        if(i < n-2 && matrix[i+2][j] == 'E' && !down_barrier[i+1][j]) ans[1] = {-1,-1};

    }
    if(j > 0 && (matrix[i][j-1] == '.' || matrix[i][j-1] == '*') && !left_barrier[i][j]){
        ans[2] = {i,j-1};
        if(!left_barrier[i][j-1] && j==1) ans[2] = {-1, -1};
        if(j > 1 && (matrix[i][j-2] == '.' || matrix[i][j-2] == '*') && !left_barrier[i][j-1]){
            ans[2] = {i,j-2};
        }
        if(j > 1 && matrix[i][j-2] == 'E' && !left_barrier[i][j-1]){
            ans[2] = {-1, -1};
        }
    }
    if(i > 0 && (matrix[i-1][j] == '.' || matrix[i-1][j] == '*') && !up_barrier[i][j]){
        ans[3] = {i-1,j};
        if(!up_barrier[i-1][j] && i == 1) {
            ans[3] = {-1,-1};
        }
        if(i > 1 && (matrix[i-2][j] == '.' || matrix[i-2][j] == '*') && !up_barrier[i-1][j]){
            ans[3] = {i-2,j};
        }
        if(i > 1 && matrix[i-2][j] == 'E' && !up_barrier[i-1][j]){
            ans[3] = {-1, -1};
        }
    }
    return ans;
}

vector<pair<int,int>> get_flying_moves(vector<string> &matrix, int i, int j, int jump){
    int n = matrix.size();
    int m = matrix[0].size();
    vector<pair<int,int>> ans(4, {-1,-1});
    int r = j+jump;
    for(;r<m;r++){
        if(matrix[i][r] == 'E') break;
        if(matrix[i][r] == '*' or matrix[i][r] == '.'){
            ans[0] = {i,r};
            break;
        }
    }
    

    r = i+jump;
    for(;r<n;r++){
        if(matrix[r][j] == 'E') break;
        if(matrix[r][j] == '*' or matrix[r][j] == '.'){
            ans[1] = {r, j};
            break;
        }
    }


    r = j-jump;
    for(;r>=0;r--){
        if(matrix[i][r] == 'E') break;
        if(matrix[i][r] == '*' or matrix[i][r] == '.'){
            ans[2] = {i,r};
            break;
        }
    }


    r = i-jump;
    for(;r>=0;r--){
        if(matrix[r][j] == 'E') break;
        if(matrix[r][j] == '*' or matrix[r][j] == '.'){
            ans[3] = {r, j};
            break;
        }
    }
    return ans;
}

bool foo(vector<string> &matrix, int moves, vector<pair<vector<int>, string>> &solution, int star){
    int n = matrix.size();
    int m = matrix[0].size();
    if(maintain_state){
        mp[matrix] = moves;
    }
    if(star == 0){
        return true;
    }
    if(star > moves){
        return false;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(matrix[i][j] == 'S'){
               vector<pair<int,int>> mv = get_snail_moves(matrix, i, j);
               for(int g=0;g<4;g++){
                auto it = mv[g];
                if(!(it.first == -1 and it.second == -1)){
                    matrix[i][j] = '.';
                    if(matrix[it.first][it.second] == '.'){
                        matrix[it.first][it.second] = 'S';
                        solution.push_back({{i,j,g}, "Snail"});
                        if(foo(matrix, moves-1, solution, star)) return true;
                        solution.pop_back();
                        matrix[i][j] = 'S';
                        matrix[it.first][it.second] = '.';
                    }
                    else if(matrix[it.first][it.second] == '*'){
                        matrix[it.first][it.second] = '.';
                        solution.push_back({{i,j,g}, "Snail"});
                        if(foo(matrix, moves-1, solution, star-1)) return true;
                        solution.pop_back();
                        matrix[i][j] = 'S';
                        matrix[it.first][it.second] = '*';
                    }
                }
               }         
            }
            else if(matrix[i][j] == 'G'){
                vector<pair<int,int>> mv = get_flying_moves(matrix, i, j, 1);
                for(int g=0;g<4;g++){
                    auto it = mv[g];
                    if(!(it.first == -1 and it.second == -1)){
                        matrix[i][j] = '.';
                        if(matrix[it.first][it.second] == '.'){
                            matrix[it.first][it.second] = 'G';
                            if(maintain_state && moves -1 <= mp[matrix]){
                                continue;
                            }
                            solution.push_back({{i,j,g}, "Grasshopper"});
                            if(foo(matrix, moves-1, solution, star)) return true;
                            solution.pop_back();
                            matrix[i][j] = 'G';
                            matrix[it.first][it.second] = '.';
                        }
                        else if(matrix[it.first][it.second] == '*'){
                            if(maintain_state && moves -1 <= mp[matrix]){
                                continue;
                            }
                            matrix[it.first][it.second] = '.';
                            solution.push_back({{i,j,g}, "Grasshopper"});
                            if(foo(matrix, moves-1, solution, star - 1)) return true;
                            solution.pop_back();
                            matrix[i][j] = 'G';
                            matrix[it.first][it.second] = '*';
                        }
                    }
               }         
            }
            else if(matrix[i][j] == 'P'){
                vector<pair<int,int>> mv = get_spider_moves(matrix, i, j);
                for(int g=0;g<4;g++){
                    auto it = mv[g];
                    if(!(it.first == -1 and it.second == -1)){
                        matrix[i][j] = '.';
                        if(matrix[it.first][it.second] == '.'){
                            matrix[it.first][it.second] = 'P';
                            solution.push_back({{i,j,g}, "Spider"});
                            if(foo(matrix, moves-1, solution, star)) return true;
                            solution.pop_back();
                            matrix[i][j] = 'P';
                            matrix[it.first][it.second] = '.';
                        }
                        else if(matrix[it.first][it.second] == '*'){
                            matrix[it.first][it.second] = '.';
                            solution.push_back({{i,j,g}, "Spider"});
                            if(foo(matrix, moves-1, solution, star-1)) return true;
                            solution.pop_back();
                            matrix[i][j] = 'P';
                            matrix[it.first][it.second] = '*';
                        }
                    }
               }         
            }
            else if(matrix[i][j] == 'L'){
                vector<pair<int,int>> mv = get_ladybug_moves(matrix, i, j);
                for(int g=0;g<4;g++){
                    auto it = mv[g];
                    if(!(it.first == -1 and it.second == -1)){
                        matrix[i][j] = '.';
                        if(matrix[it.first][it.second] == '.'){
                            matrix[it.first][it.second] = 'L';
                            solution.push_back({{i,j,g}, "Ladybug"});
                            if(foo(matrix, moves-1, solution, star)) return true;
                            solution.pop_back();
                            matrix[i][j] = 'L';
                            matrix[it.first][it.second] = '.';
                        }
                        else if(matrix[it.first][it.second] == '*'){
                            matrix[it.first][it.second] = '.';
                            solution.push_back({{i,j,g}, "Ladybug"});
                            if(foo(matrix, moves-1, solution, star-1)) return true;
                            solution.pop_back();
                            matrix[i][j] = 'L';
                            matrix[it.first][it.second] = '*';
                        }
                    }
               }         
            }
            else if(matrix[i][j] == 'B'){
                vector<pair<int,int>> mv = get_flying_moves(matrix, i, j, 2);
                for(int g=0;g<4;g++){
                    auto it = mv[g];
                    if(!(it.first == -1 and it.second == -1)){
                        matrix[i][j] = '.';
                        if(matrix[it.first][it.second] == '.'){
                            matrix[it.first][it.second] = 'B';
                            solution.push_back({{i,j,g}, "Bumblebee"});
                            if(foo(matrix, moves-1, solution, star)) return true;
                            solution.pop_back();
                            matrix[i][j] = 'B';
                            matrix[it.first][it.second] = '.';
                        }
                        else if(matrix[it.first][it.second] == '*'){
                            matrix[it.first][it.second] = '.';
                            solution.push_back({{i,j,g}, "Bumblebee"});
                            if(foo(matrix, moves-1, solution, star - 1)) return true;
                            solution.pop_back();
                            matrix[i][j] = 'B';
                            matrix[it.first][it.second] = '*';
                        }
                    }
               }         
            }
            else if(matrix[i][j] == 'U'){
                vector<pair<int,int>> mv = get_flying_moves(matrix, i, j, 3);
                for(int g=0;g<4;g++){
                    auto it = mv[g];
                    if(!(it.first == -1 and it.second == -1)){
                        matrix[i][j] = '.';
                        if(matrix[it.first][it.second] == '.'){
                            matrix[it.first][it.second] = 'U';
                            solution.push_back({{i,j,g}, "Butterfly"});
                            if(foo(matrix, moves-1, solution, star)) return true;
                            solution.pop_back();
                            matrix[i][j] = 'U';
                            matrix[it.first][it.second] = '.';
                        }
                        else if(matrix[it.first][it.second] == '*'){
                            matrix[it.first][it.second] = '.';
                            solution.push_back({{i,j,g}, "Butterfly"});
                            if(foo(matrix, moves-1, solution, star - 1)) return true;
                            solution.pop_back();
                            matrix[i][j] = 'U';
                            matrix[it.first][it.second] = '*';
                        }
                    }
               }         
            }
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    int moves = stoi(argv[1]);
    string filePath = argv[2]; 
    auto gridData = parseInputFile(filePath);
    // cout << "Rows: " << gridData.size() << ", Columns: " << gridData[0].size() << endl;
    // cout << "Grid Matrix:" << endl;
    int star = 0;
    for (const auto& row : gridData) {
        for (char cell : row) {
            if(cell == '*'){
                star++;
            }
            // cout << cell;
        }
        // cout << endl;
    }
    print_info();
    if(moves < min_moves){
        cout<<"No solution possible with given number of moves\n";
    }
    else{
        moves = min_moves;
    }
    if(moves > 13){
        maintain_state = true;  // applying heuristic is beneficial when there are large number of moves
    }
    vector<pair<int,int>> tmp;
    map<int, string> mp1;
    mp1[0] = "Right";
    mp1[1] = "Down";
    mp1[2] = "Left";
    mp1[3] = "Up";
    vector<pair<vector<int>, string>> solution;
    if(foo(gridData, moves, solution, star)){
        for(auto it:solution){
            cout<<"Move "<< it.second<<" from ("<<it.first[0]<<", "<<it.first[1]<<") in "<<mp1[it.first[2]]<<" direction\n";
        }
    }
    else{
        cout<<"No solution possible with given number of moves\n";
    }
    return 0;
}
