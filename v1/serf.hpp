////////////////////////////////////////////////////////////

const int taille = 20;
int amplitude = 12;
float vitesse = 0.4;
const int config[2] = {8,8}; //nb_boids in row and col, respectively
int width = 1700;
int height = 1050;
const int zone_prox = 10*taille;
const int zone_align = 5*taille;
const int zone_collision = taille*3;


const float cote = taille*3 / (2*sqrt(3));
const int fps = 30;
const int marge = 50;
int nb_step = 0;
const int nb_serf = config[0]*config[1];

int degre;
bool mur;
int row;
int col;
sf::ContextSettings options;
sf::VertexArray list_serf[nb_serf];
std::vector<float> long_pas;
std::vector<float> pas;
std::vector<float> centre;
sf::RenderWindow window;
