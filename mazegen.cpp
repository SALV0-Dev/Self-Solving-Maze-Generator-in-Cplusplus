#include <iostream>
#include <vector>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Grid {
    public: 
        Grid(int rows, int columns);
        void Print();
        std::vector< std::vector<std::string> > ReturnMaze() { return mazeGrid; }
        int PossibleNeighbours(int i, int j);
        void Maze();
    private:
        int nbrOfRows;
        int nbrOfColumns;
        std::vector< std::vector<std::string> > mazeGrid;
        std::vector< std::vector<bool> > boolVector;
};
Grid::Grid (int rows, int columns){
    nbrOfRows = (rows * 2) + 1;
    nbrOfColumns = (columns * 2) + 1;
    mazeGrid.resize(nbrOfRows, std::vector<std::string> (nbrOfColumns));
    boolVector.resize(nbrOfRows, std::vector<bool> (nbrOfColumns));

    for (int i = 0; i < nbrOfRows; ++i){
        if (i % 2 == 0){
            for (int j = 0; j < nbrOfColumns; ++j){
                if (j % 2 == 0){
                    mazeGrid.at(i).at(j) = "+";
                }
                else{
                    mazeGrid.at(i).at(j) = "---";
                }
            }
        }
        else{
            for (int j = 0; j < nbrOfColumns; ++j){
                if (j % 2 == 0){
                    mazeGrid.at(i).at(j) = "|";
                }
                else{
                    mazeGrid.at(i).at(j) = "   ";
                }
            }
        }
    }
}
int Grid::PossibleNeighbours(int i, int j){
    int count = 0;
    
    if (i - 2 > 0 && boolVector.at(i - 2).at(j) == false){
        count = count + 1;
    }
    if (i + 2 < nbrOfRows && boolVector.at(i + 2).at(j) == false){
        count = count + 1;
    } 
    if (j - 2 > 0 && boolVector.at(i).at(j - 2) == false){
        count = count + 1;
    }
    if (j + 2 < nbrOfColumns && boolVector.at(i).at(j + 2) == false){
        count = count + 1;
    }

    return count;
}
void Grid::Maze(){
    int i = 1;
    int j = 1;
    int toVisit = ((nbrOfRows - 1) / 2) * ((nbrOfColumns - 1) / 2) - 1;
    std::stack< std::pair<int,int> > gridStack;
    std::vector< std::vector<int> > temp;
    int index;
    int rndNum;
    int previousI;
    int previousJ;

    boolVector.at(i).at(j) = true;
    gridStack.push({i, j});

    while (toVisit != 0){
        i = gridStack.top().first;
        j = gridStack.top().second;

        if (PossibleNeighbours(i, j) > 0){          //Select one out of all possibleNeighbours                 
            previousI = i;
            previousJ = j;
            index = 0;
            temp.clear();

            temp.resize(2, std::vector<int>(PossibleNeighbours(i,j)));
                                            
            if (i - 2 > 0 && boolVector.at(i - 2).at(j) == false){
                temp.at(0).at(index) = i - 2;
                temp.at(1).at(index) = j;
                index = index + 1;
            }
            if (i + 2 < nbrOfRows && boolVector.at(i + 2).at(j) == false){
                temp.at(0).at(index) = i + 2;
                temp.at(1).at(index) = j;
                index = index + 1;
            }
            if (j - 2 > 0 && boolVector.at(i).at(j - 2) == false){
                temp.at(0).at(index) = i;
                temp.at(1).at(index) = j - 2;
                index = index + 1;
            }
            if (j + 2 < nbrOfColumns && boolVector.at(i).at(j + 2) == false){
                temp.at(0).at(index) = i;
                temp.at(1).at(index) = j + 2;
                index = index + 1;
            }

            rndNum = rand() % PossibleNeighbours(i, j);      

            i = temp.at(0).at(rndNum);             //Choose a random Neighbour
            j = temp.at(1).at(rndNum);
            boolVector.at(i).at(j) = true;         //boolVector.at(Neighbour) = true;

            gridStack.push({i, j});                //Push Neighbour on stack 

            if (i > previousI){                    //Delete in-between wall
                mazeGrid.at(i - 1).at(j) = "   ";
            }
            if (i < previousI){
                mazeGrid.at(i + 1).at(j) = "   ";
            }
            if (j > previousJ){
                mazeGrid.at(i).at(j - 1) = " ";
            }
            if (j < previousJ){
                mazeGrid.at(i).at(j + 1) = " ";
            }   

            toVisit = toVisit - 1;
        }
        else{
            gridStack.pop();
        }    
    }
}

class Solver {
    public:
        void GetMaze(int nRows, int nColumns);
        int GoTo(int i, int j);
        void SolveMaze();
        void Print();
    private:
        int numRows;
        int numColumns;
        std::vector< std::vector<std::string> > Maze;
        std::vector< std::vector<bool> > boolMaze; 
};
void Solver::GetMaze(int nRows, int nColumns){
    Grid unsolvedMaze(nRows, nColumns);
    numRows = (nRows * 2) + 1;
    numColumns = (nColumns * 2) + 1;
    unsolvedMaze.Maze();
    Maze = unsolvedMaze.ReturnMaze();
    boolMaze.resize(numRows, std::vector<bool>(numColumns));
}
int Solver::GoTo(int i, int j){
    int count = 0;

    if (Maze.at(i - 1).at(j) != "---" && boolMaze.at(i - 2).at(j) == false){
        count = count + 1;
    }
    if (Maze.at(i + 1).at(j) != "---" && boolMaze.at(i + 2).at(j) == false){
        count = count + 1;
    }
    if (Maze.at(i).at(j - 1) != "|" && boolMaze.at(i).at(j - 2) == false){
        count = count + 1;
    }
     if (Maze.at(i).at(j + 1) != "|" && boolMaze.at(i).at(j + 2) == false){
        count = count + 1;
    }    

    return count;
}
void Solver::SolveMaze(){
    int i = 1;
    int j = 1;
    std::stack< std::pair<int,int> > solverStack;
    std::vector< std::vector<int> > temp;
    int index;
    int RndNum;
    
    solverStack.push({i, j});
    boolMaze.at(i).at(j) = true;
    Maze.at(i).at(j) = " . ";

    while (solverStack.top().first != numRows - 2 || solverStack.top().second != numColumns - 2){
        i = solverStack.top().first;
        j = solverStack.top().second;

        if (GoTo(i, j) > 0){
            index = 0;
            temp.clear();
            temp.resize(2, std::vector<int> (GoTo(i, j)));

            if (Maze.at(i - 1).at(j) != "---" && boolMaze.at(i - 2).at(j) == false){
                temp.at(0).at(index) = i - 2;
                temp.at(1).at(index) = j;
                index = index + 1;
            }
            if (Maze.at(i + 1).at(j) != "---" && boolMaze.at(i + 2).at(j) == false){
                temp.at(0).at(index) = i + 2;
                temp.at(1).at(index) = j;
                index = index + 1;
            }
            if (Maze.at(i).at(j - 1) != "|" && boolMaze.at(i).at(j - 2) == false){
                temp.at(0).at(index) = i;
                temp.at(1).at(index) = j - 2;
                index = index + 1;
            }
            if (Maze.at(i).at(j + 1) != "|" && boolMaze.at(i).at(j + 2) == false){
                temp.at(0).at(index) = i;
                temp.at(1).at(index) = j + 2;
                index = index + 1;
            }

            RndNum = rand() % GoTo(i, j);      

            i = temp.at(0).at(RndNum);             
            j = temp.at(1).at(RndNum);
            boolMaze.at(i).at(j) = true;         

            solverStack.push({i, j});
            Maze.at(i).at(j) = " . "; 
        }
        else{
            Maze.at(i).at(j) = "   ";
            solverStack.pop();
        }
    }
}
void Solver::Print(){ 
    for (int i = 0; i < numRows; ++i){
        for (int j = 0; j < numColumns; ++j){
            std::cout << Maze.at(i).at(j);
        }
        std::cout << std::endl;
    }
}

int main(int argc, char *argv[]){

    int nbrRows;
    int nbrColumns;
    int seedVal;

    if (argc < 3){
        std::cout << "error" << std::endl;
        return 1;
    }

    if (argv[3]){
        seedVal = atoi (argv[3]);
        srand(seedVal);
    }
    else{
        srand(time(NULL));
    }

    nbrRows = atoi (argv[1]);
    nbrColumns = atoi (argv[2]);

    Solver x;
    x.GetMaze(nbrRows,nbrColumns);
    x.SolveMaze();
    x.Print();

    return 0;
}