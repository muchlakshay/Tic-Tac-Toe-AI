#include <iostream>
#include <random>
#include <chrono>

char grids[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};

void draw();
bool isEmpty(int grid_index);
bool isFull();
bool isWon(char marker);
void mark(char marker, int grid_index);
char askMarker();
int askGrid();
int minimax(bool maximize, char u_mark, char c_mark);


int main(){
    char user_marker {askMarker()};
    char computer_marker {(user_marker=='O') ? 'X' : 'O'};
    
    while (true){
        draw();
        int user_grid {askGrid()};
        if (!isEmpty(user_grid)){
            std::cout<<"\n\nAlready Taken\n\n";
            continue;
        }
        mark(user_marker, user_grid);
        if(isWon(user_marker)){
            draw();
            std::cout<<"\n\nYou Won!\n\n";
            break;
        }
        if(isFull()){
            draw();
            std::cout<<"\n\nDraw!\n\n";
            break;
        }
        int computer_grid {};
        int bestScore {-1000};
        for (int i {1}; i<=9; ++i){
            if (isEmpty(i)){
                mark(computer_marker, i);
                int score {minimax(false, user_marker, computer_marker)};
                mark(' ', i);
                // std::cout<<i<<" - "<<score<<"\n";
                if (score>bestScore){
                    bestScore=score;
                    computer_grid = i;
                }
            }
        }
        mark(computer_marker, computer_grid);
        if(isWon(computer_marker)){
            draw();
            std::cout<<"\n\nYou Lost!\n\n";
            break;
        }
        if(isFull()){
            draw();
            std::cout<<"\n\nDraw!\n\n";
            break;
        }
    }
    return 0;
}

int minimax(bool maximize, char u_mark, char c_mark){
    if (isWon(u_mark)) return -1;
    if (isWon(c_mark)) return 1;
    if (isFull()) return 0;

    if (maximize){
        int bestScore {-1000};
        for (int i{1}; i<=9; i++){
            if(isEmpty(i)){
                mark(c_mark, i);
                int score {minimax(false, u_mark, c_mark)};
                mark(' ', i);
                bestScore = std::max(bestScore, score);
            }
        }
        return bestScore; 
    }
        else{
            int bestScore {1000};
            for (int i{1}; i<=9; i++){
                if(isEmpty(i)){
                    mark(u_mark, i);
                    int score {minimax(true, u_mark, c_mark)};
                    mark(' ', i);
                    bestScore = std::min(bestScore, score);
                }
            }
            return bestScore; 
        }
}

int askGrid(){
    while (true){
        int inp {};
        std::cout<<"Enter Grid (1-9): ";
        std::cin>>inp;

        if (inp>0 && inp<10){
            return inp; 
        }
        std::cout<<"\nInvalid Choice!\n";
        std::cin.clear();
        std::cin.ignore(100,'\n');
    }
}

char askMarker(){
    while (true){
        char inp {};
        std::cout<<"Enter Choice (O or X): ";
        std::cin>>inp;

        if (inp!='O' && inp!='X'){
            std::cout<<"\nInvalid Choice!\n";
            continue;
        }
        return inp; 
    }
}

void mark(char marker, int grid_index){
    grids[grid_index-1] = marker;
}

bool isWon(char marker){
    for (int i {0}; i<=2; ++i){
        if(grids[i]==marker && grids[i]==grids[i+3] 
           && grids[i+3]==grids[i+6])
            return true;
    }
    for (int i {0}; i<=6; i+=3){
        if(grids[i]==marker && grids[i]==grids[i+1] 
          && grids[i+1]==grids[i+2])
            return true;
    }
    if (grids[0]==marker && grids[0] == grids[4] 
        && grids[4]==grids[8])
            return true;
    if (grids[2]==marker && grids[2] == grids[4] 
        && grids[4]==grids[6])
            return true;

    return false;
}

bool isFull(){
    bool full {true};
    for (int i {0}; i<=8; ++i){
        if (grids[i]==' ')
            full=false;
    }
    return full;
}

bool isEmpty(int grid_index){
    return ((grids[grid_index-1])==' ') ? true : false;
}

void draw(){
    std::cout<<"\n     |"<<"     |"<<"     "<<"\n";
    std::cout<<"  "<<grids[0]<<"  |"<<"  "<<grids[1]<<"  |"<<"  "<<grids[2]<<"   "<<"\n";
    std::cout<<"_____|"<<"_____|"<<"_____"<<"\n";
    std::cout<<"     |"<<"     |"<<"     "<<"\n";
    std::cout<<"  "<<grids[3]<<"  |"<<"  "<<grids[4]<<"  |"<<"  "<<grids[5]<<"   "<<"\n";
    std::cout<<"_____|"<<"_____|"<<"_____"<<"\n";
    std::cout<<"     |"<<"     |"<<"     "<<"\n";
    std::cout<<"  "<<grids[6]<<"  |"<<"  "<<grids[7]<<"  |"<<"  "<<grids[8]<<"   "<<"\n";
    std::cout<<"     |"<<"     |"<<"     "<<"\n\n";
}
