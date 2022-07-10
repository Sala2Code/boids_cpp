// ! V2 : Horizontal moving 

////////////////////////////////////////////////////////////
//You can modify this :

const int width = 1700; //Window
const int height = 1050; //Window
const int taille = 40; //Boid
int amplitude = 20; //Not really useful
const int zone_prox = 8*taille; 
const int zone_align = 4*taille;
const int zone_collision = taille*1.5; 
float vitesse = 0.5; //Speed
const int nb_total = 50; //Number of boids after generation
const int speed_generate = 30; //Accelerate the generation
const int nb_to_generate = 3; //For each generation how can be generated.


////////////////////////////////////////////////////////////
//For the V1, let like that
const int marge = 50; //Distance to the window's bordure 
const int config[2] = {2,2}; //row , col

////////////////////////////////////////////////////////////
sf::ContextSettings options;
const int fps = 30;
const float cote = taille*3 / (2*sqrt(3));
int nb_step = 0;
int nb_serf = config[0]*config[1];
sf::VertexArray list_serf[nb_total];

int degre;
bool mur;
int row;
int col;
std::vector<float> long_pas;
std::vector<float> pas;
std::vector<float> centre;
sf::RenderWindow window;

////////////////////////////////////////////////////////////