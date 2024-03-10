/* 
-2 = Sels Minéraux
-1 = terre
0 = Herbe
1 = Moutons
2 = Loups
*/

using namespace std;

struct s_pos{
    int x;
    int y;
};
typedef struct s_pos pos;

class Animal{
    public :
        int animaltype;
        int age = 0;
        int saturation;
        int sexe;
        int x;
        int y;
        int move=0;

    char check_world[7][7];
    int verif_sheep();
    int verif_wolf();
    bool operator==(int otherType) const {
        return (animaltype == otherType);
    };

    void moves(pos* mouves);
};

class Life{
    public :
        Animal type;
        int grass;

        Life& operator=(int value) {
            grass = value;
            return *this;
        };

        bool operator==(int value) const {
            return (type.x - 1) == value && (type.y - 1) == value;
        };


        void Univers_Init();
        void print_world();
        void mouton_Init();
        void loup_Init();
        int random_intervalle(int a, int b);

        void reset(Life life);
        static Life world[7][7];
};



int moveset(Life& life);