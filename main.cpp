#include <iostream>
#include <thread>
#include <chrono>

#include "snake.h"
#include "screen.h"
#include "board.h"
#include "keyboard.h"
#include "borders.h"
#include "generator_fruit.h"


#define UP_ARROW    65 //On définit les touches du clavier qui vont permettre de intéragir
#define LEFT_ARROW  68
#define DOWN_ARROW  66
#define RIGHT_ARROW 67

// Variables de contexte du board

std::vector<std::pair<int,int>> snake; //Je définie le snake comme ceci, l'avantage est que l'ordre donné par le vector
                                       //est l'ordre du snake : le premier élément est la queue, le dernier la tête.

std::pair<int,int> coordhaut {1,1}; //Le haut gauche de la grille est à (1,1). On définit la taille de la grille de jeux, 
std::pair<int,int> coordbas {11,21};//bords inclus ici

std::map<std::pair<int,int>,bool> borders_map; //La carte des bordures, après réfléxion, un std::vector aurait suffit.
std::map<std::pair<int,int>,bool> board_map; //La carte de la grille de jeux


// Variables de contexte du snake
int snake_size = 5; // J'ai choisi de démarer avecun snake de taille 5 pour l'instant. A CHANGER

std::vector<snake_segment_st> snake_segments; //Par compris comment l'utiliser
std::map<std::pair<int,int>,bool> snake_board; //Non plus, j'ai pas compris comment savoir dans quel ordre le snake est

int main(int, char**) {
    typedef std::chrono::high_resolution_clock time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;
    std::cout << "Snake starting...\n";

    borders(borders_map,coordhaut,coordbas);
    inside_board(board_map,coordhaut,coordbas);
    
    keyboard_init();
    int x = 2; //On démarre en haut à droite de la grille
    int y = snake_size+1;
    std::string mouv {"RIGHT"}; //On choisit au départ que le snake part à droite

    for(int i =2;i<=snake_size+1;i++){ //Je définis le snake à afficher initialement
        std::pair<int,int> pix {x,i};
        snake.push_back(pix);
    }

    std::pair<int,int> posi_of_fruit; //On définit le fruit initial 
    posi_of_fruit=posi_fruit(coordhaut,coordbas);
    
    std::pair<int,int> ancient_queue; //L'ancienne queue du serpent avant son déplacement
    bool bool_for_while = true;
    while (bool_for_while) //On démarre le jeux, il faudra mettre un cadençage + le fait que le snake continue en 
                 //ligne droite quand on ne touche à rien/
    {

        // Affichage de la scène
        screen_clear();
        screen_draw_inside_board(board_map); //La grille
        screen_draw_borders(borders_map); //La bordure
        screen_draw_fruit(posi_of_fruit); //Le fruit
        screen_draw_snake(snake); //Le snake

        // Lecture clavier et actions
        int rafraichissement = 200; //Il faut que ça soit le même que celui du keyboard
        double conversion = 1000;
        
        auto temps1 = time::now();
        auto temps2 = temps1;

        fsec final =temps2-temps1;


        
        int key_scan = keyboard_scan();
        std::string continu;
        if (key_scan==27 or key_scan==91){ //Je sais pas pourqoi mais dès que j'appui sur une touhe il fait cette séquence d'abord...
    
            continu="NO";
        }
        else{
            continu="YES"; //La variable qui permet de savoir si on a exécuté la séquence foireuse.
        }
        //Si on appuie sur une touche, le keyboard_scan se coupe, il faut donc faire attendre le programme de manière 
        //à ce que le serpent se déplace à vitesse constante.
        if ((key_scan == UP_ARROW) or (key_scan == DOWN_ARROW) or (key_scan == RIGHT_ARROW) or (key_scan == LEFT_ARROW)){
            temps2=time::now();
            final = temps2-temps1;
            auto sec = final.count();
            std::this_thread::sleep_for (ms ( (int) (rafraichissement - sec*conversion - 100) ) ); //Le 100 a été ajouté pour que plus réalisme dans le déplacement (pas de saccades)
        }

        //On distingue le cas où on continue car on n'appuie sur rien (on continue dans la direction précédente) *
        //et le cas où l'on change de direction.
        if (continu=="YES" and not((key_scan==UP_ARROW) or (key_scan==DOWN_ARROW) or (key_scan==LEFT_ARROW) or (key_scan==RIGHT_ARROW))){
        
            if (mouv=="UP"){
                x--;
            }
            else if(mouv=="DOWN"){
                x++;
            }
            else if(mouv=="LEFT"){
                y--;
            }
            else if(mouv=="RIGHT"){
                y++;
            }
            ancient_queue = pop_front(snake); //On change le snake par effet de bord + on récupère l'ancienne queue
            snake.push_back({x,y}); //On rajoute la nouvelle tête
        }
        else{ //Ie une des touches est enfoncée
        //if (not((mouv=="UP" and key_scan==UP_ARROW) or (mouv=="DOWN" and key_scan==DOWN_ARROW) or (mouv=="LEFT" and key_scan==LEFT_ARRO) or (mouv="RIGHT" and key_scan==RIGHT_ARROW))){
        
        if (key_scan == UP_ARROW)
        {
            mouv = "UP";
            x--;
            ancient_queue = pop_front(snake); //On change le snake par effet de bord + on récupère l'ancienne queue
            snake.push_back({x,y}); //On rajoute la nouvelle tête
        }
        else if (key_scan == DOWN_ARROW)
        {
            mouv = "DOWN"; //On enregistre le mouv effectué pour le prochain coup dans le cas où l'on appuie sur aucune touche.
            x++;
            ancient_queue = pop_front(snake);
            snake.push_back({x,y});
        }
        else if (key_scan == LEFT_ARROW)
        {   
            mouv = "LEFT";
            y--;
            ancient_queue = pop_front(snake);
            snake.push_back({x,y});
        }
        else if (key_scan == RIGHT_ARROW)
        {
            mouv ="RIGHT";
            y++;
            ancient_queue = pop_front(snake);
            snake.push_back({x,y});
        }

        //}//Fin if
        }//Fin else

        // Contrôle  des limites
        if (x < 0) x=0;
        if (y < 0) y=0;

        //Si le snake lange le fruit :
        if (snake.back()==posi_of_fruit){
            posi_of_fruit=posi_fruit(coordhaut,coordbas);//On génère un nouveau fruit
            if (fruit_on_snake(snake,posi_of_fruit)){ //On regarde s'il est sur le snake
                int taille = (coordbas.first - coordhaut.first)*(coordbas.second - coordhaut.second);
                if (snake.size() >= taille/2){ //Si le snake est suffisamment grand, on crée le nouveau fruit de manière intelligente
                    posi_of_fruit=gene_fruit_out_snake(snake,board_map,posi_of_fruit); //La posi du fruit est inutile à enlever
                }
                else{ //Sinon, on génère de manière aléatoire --> de bonnes chances que le fruit ne soit pas sur le snake.
                    posi_of_fruit=posi_fruit(coordhaut,coordbas);
                    while(fruit_on_snake(snake,posi_of_fruit)){ //On génère tant qu'il est sur le snake.
                        posi_of_fruit=posi_fruit(coordhaut,coordbas);
                    }
                }
                
            }
            snake_growth(snake,ancient_queue); //Agit par effet de bord aussi, on fait grandir le snake.


        }
        if (snake_eat_himself(snake)){ //S'il se mange soit même
            screen_clear();
            std::cout <<"Game over" <<std::endl;
            bool_for_while=false;
            //On pourra demander plus tard si l'on veut rejouer A FAIRE
        }
        if (snake_touch_borders(snake,borders_map)){ //S'il touche la bordure
            screen_clear();
            std::cout<< "Game Over" <<std::endl;
            bool_for_while=false;
            
        }
        key_scan=0; //Pas forcément utile.

        //std::this_thread::sleep_for (ms(1000));

        // Exemple d'attente si besoin était (attention, suspend entièrement l'application)
        //std::this_thread::sleep_for (std::chrono::milliseconds(100));
    }

    keyboard_end();

}
