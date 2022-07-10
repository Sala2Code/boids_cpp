////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

#include <cmath>
#include <math.h>       
#define PI 3.14159265

// ! Change the path for you !
#include <SFML/serf.hpp> 


////////////////////////////////////////////////////////////
// Turn the boid according to the angle.
sf::Vector2f coord(float Wx,float Wy,float Zx,float Zy,int degre,std::vector<float> pas, std::vector<float> pos0 );

// Initialize the boid (boid = serf)
sf::VertexArray setSerf();

// Move the boid
sf::VertexArray serf_update(sf::VertexArray serf,int num);

// Calculate where the serf is going
float mean_neighbors(sf::VertexArray serf, int num, std::vector<float> centre);


// To know if the serf go to the left or the right according to his neighbor
float angleDeviate(float angle, float angle_add, std::vector<float> pos0_init, sf::VertexArray serf, bool collision, std::vector<float> centre, float Yx, float Yy);

////////////////////////////////////////////////////////////
int main(){

    sf::RenderWindow window(sf::VideoMode(width,height), "Essaims");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(fps);
    options.antialiasingLevel = 8;



    for(int i=0;i<nb_serf;i++){
        list_serf[i] = setSerf();
    }

    while (window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black); 
        
        // Generate
        if(nb_step%(fps/speed_generate)==0 && nb_serf<nb_total-nb_to_generate){
            int nb_sup = rand()%nb_to_generate;
            for(int i=nb_serf-1;i<nb_serf+nb_sup;i++){
                list_serf[i] = setSerf();
            }
            nb_serf +=nb_sup;
        }


        // Update
        for(int i=0;i<nb_serf;i++){
            window.draw(list_serf[i]);
            list_serf[i] = serf_update(list_serf[i],i);
            // Delete those which left
            if(list_serf[i][0].position.x>width || list_serf[i][0].position.y>height+marge || list_serf[i][0].position.y<-marge){
                list_serf[i] = setSerf();
            }
            
        }

        window.display();
        if(nb_step<nb_total){
            nb_step++; //to avoid wasting memory
        }
    }
    return 0;
}

// W centre de gravité, Z point initial
sf::Vector2f coord(float Wx,float Wy,float Zx,float Zy,float degre,std::vector<float> pas,std::vector<float> pos0 ){
    float rad = degre - acos((pos0[0] - Wx- width/2)/(sqrt(pow(pos0[0] - Wx- width/2,2) + pow(pos0[1] - Wy - height/2,2) )));
    float x = Wx + cos(rad)*(Zx-Wx) - sin(rad)*(Zy-Wy) + pas[0];
    float y = Wy + cos(rad)*(Zy-Wy) + sin(rad)*(Zx-Wx) + pas[1];
    return sf::Vector2f(x, y);
}

sf::VertexArray setSerf(){
    sf::VertexArray serviteur(sf::Triangles, 3);
    // h = a*sqrt(3) / 2
    // R (rayon circonscrit) = a*sqrt(3)/3
    serviteur[0].position = sf::Vector2f(0,rand()%height);
    serviteur[1].position = sf::Vector2f(serviteur[0].position.x - 0.5*cote, serviteur[0].position.y + sqrt(3)*cote/2);
    serviteur[2].position = sf::Vector2f(serviteur[0].position.x + 0.5*cote, serviteur[0].position.y + sqrt(3)*cote/2);
    serviteur[0].color = sf::Color::Red;

    float angle_init = (237 + amplitude/2 - rand()%amplitude )*PI/180;  //237 vient d'un prolème d'angle que j'ai la flemme de comprendre. Normalement c'est 270
    std::vector<float> pos0_init{serviteur[0].position.x,serviteur[0].position.y};
    std::vector<float> pas_nul{0,0};
    centre = {(serviteur[0].position.x+serviteur[1].position.x+serviteur[2].position.x)/3, (serviteur[0].position.y+serviteur[1].position.y+serviteur[2].position.y)/3};

    serviteur[0].position = coord(centre[0],centre[1],serviteur[0].position.x,serviteur[0].position.y,angle_init,pas_nul,pos0_init);
    serviteur[1].position = coord(centre[0],centre[1],serviteur[1].position.x,serviteur[1].position.y,angle_init,pas_nul,pos0_init);
    serviteur[2].position = coord(centre[0],centre[1],serviteur[2].position.x,serviteur[2].position.y,angle_init,pas_nul,pos0_init);


    return serviteur;
}

sf::VertexArray serf_update(sf::VertexArray serf, int num){
    centre = {(serf[0].position.x+serf[1].position.x+serf[2].position.x)/3, (serf[0].position.y+serf[1].position.y+serf[2].position.y)/3};
    long_pas = {(serf[0].position.x - centre[0])*3, (serf[0].position.y - centre[1])*3};
    pas = {(serf[0].position.x - centre[0])*vitesse, (serf[0].position.y - centre[1])*vitesse};
    float degre = mean_neighbors(serf,num,centre);

    std::vector<float> pos0_init{serf[0].position.x,serf[0].position.y};
    sf::Vector2f pos0 = coord(centre[0],centre[1],serf[0].position.x,serf[0].position.y,degre,long_pas,pos0_init);

    serf[0].position = coord(centre[0],centre[1],serf[0].position.x,serf[0].position.y,degre,pas,pos0_init);
    serf[1].position = coord(centre[0],centre[1],serf[1].position.x,serf[1].position.y,degre,pas,pos0_init);
    serf[2].position = coord(centre[0],centre[1],serf[2].position.x,serf[2].position.y,degre,pas,pos0_init);

    return serf;

}

float mean_neighbors(sf::VertexArray serf, int num, std::vector<float> centre){
    float ret = 0.0f;
    int nb_neighbor = 0;
    int nb_tot_neighbor = 0;
    float sum = 0.0f;
    int d_most_near = width;
    std::vector<float> centre_near_neighbor;

    for(int i=0;i<nb_serf;i++){
        if (i!=num){
            std::vector<float> centre_neighbor{(list_serf[i][0].position.x+list_serf[i][1].position.x+list_serf[i][2].position.x)/3,(list_serf[i][0].position.y+list_serf[i][1].position.y+list_serf[i][2].position.y)/3};
            int distance = sqrt(pow(centre[0]-centre_neighbor[0],2)+pow(centre[1]-centre_neighbor[1],2));
            if (distance < d_most_near){
                d_most_near = distance;
                nb_neighbor = i;
                centre_near_neighbor = centre_neighbor;
            }
            if (distance < zone_prox){
                sum += acos((list_serf[i][0].position.x - centre_neighbor[0] - width/2)/(sqrt(pow(list_serf[i][0].position.x - centre_neighbor[0] - width/2 ,2) + pow(list_serf[i][0].position.y - centre_neighbor[1]  - height/2,2) )));
                nb_tot_neighbor++;
            }
        }
    }

    std::vector<float> pos0_init{serf[0].position.x,serf[0].position.y};
    float angle = acos((list_serf[nb_neighbor][0].position.x - centre_near_neighbor[0] - width/2)/(sqrt(pow(list_serf[nb_neighbor][0].position.x - centre_near_neighbor[0] - width/2,2) + pow(list_serf[nb_neighbor][0].position.y - centre_near_neighbor[1] - height/2,2) )));
    if(zone_collision > d_most_near){ //Eviter collision
        return angleDeviate(angle, 2*PI/180, pos0_init, serf, true, centre, list_serf[nb_neighbor][0].position.x, list_serf[nb_neighbor][0].position.y);
    }
    else if(nb_tot_neighbor!=0){
        if(zone_align<d_most_near<zone_prox){
           return angleDeviate(angle, 4*PI/180, pos0_init, serf, false, centre, list_serf[nb_neighbor][0].position.x, list_serf[nb_neighbor][0].position.y);
        }
        else{
            return sum / nb_tot_neighbor;
        }
    }
    return angle;
}

//Yx et Yy -> Positions du point auquel on souhaite se rapprocher / s'éloigner
float angleDeviate(float angle, float angle_add, std::vector<float> pos0_init, sf::VertexArray serf, bool collision, std::vector<float> centre, float Yx, float Yy){

    sf::Vector2f pos0_plus = coord(centre[0],centre[1],serf[0].position.x,serf[0].position.y,angle+angle_add,pas,pos0_init);
    sf::Vector2f pos0_moins = coord(centre[0],centre[1],serf[0].position.x,serf[0].position.y,angle-angle_add,pas,pos0_init);

    float d_plus = sqrt(pow(pos0_plus.x-Yx,2)+pow(pos0_plus.y-Yy,2));
    float d_moins = sqrt(pow(pos0_moins.x-Yx,2)+pow(pos0_moins.y-Yy,2));

    return ( (d_plus > d_moins && collision) || (d_plus < d_moins && !collision) ) ? angle + angle_add : angle - angle_add;
}

