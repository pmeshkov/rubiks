#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

/**
 * @brief Represents color values.
 * 
 * @enum Color
 */
enum Color{ W, O, G, R, B, Y };

/**
 * @brief Represents neighboring relationships between faces
 * 
 * @enum Orient
 */
enum Orient{ TOP, RIGHT, BOTTOM, LEFT };

/**
 * @brief Takes a color corresponding to a face, and gives returns a tuple storing two arrays, one storing the neighboring colors, and the other where they connect.
 * 
 * @param color
 * @return tuple<array<Color, 4>, array<Orient, 4>>
 */
tuple<array<Color, 4>, array<Orient, 4>> getNeighbors(Color color){
    switch (color)
    {
    case Color::W:
        return make_tuple(array<Color, 4>{Color::O, Color::G, Color::R, Color::B}, array<Orient, 4>{TOP, TOP, TOP, TOP});
    case Color::Y:
        return make_tuple(array<Color, 4>{Color::B, Color::R, Color::G, Color::O}, array<Orient, 4>{BOTTOM, BOTTOM, BOTTOM, BOTTOM});
    case Color::G:
        return make_tuple(array<Color, 4>{Color::O, Color::Y, Color::R, Color::W}, array<Orient, 4>{RIGHT, TOP, LEFT, BOTTOM});
    case Color::B:
        return make_tuple(array<Color, 4>{Color::R, Color::Y, Color::O, Color::W}, array<Orient, 4>{RIGHT, BOTTOM, LEFT, TOP});
    case Color::R:
        return make_tuple(array<Color, 4>{Color::G, Color::Y, Color::B, Color::W}, array<Orient, 4>{RIGHT, RIGHT, LEFT, RIGHT});
    case Color::O:
        return make_tuple(array<Color, 4>{Color::G, Color::W, Color::B, Color::Y}, array<Orient, 4>{LEFT, LEFT, RIGHT, LEFT});
    default:
        throw std::runtime_error("Unknown Color value");
    }
};

/**
 * @brief Given an orientation, return the indices of the FaceArray matrix corresponding to the orientation.
 * 
 * @param orient
 * @return array<tuple<int,int>, 3> 
 */
array<pair<int,int>, 3> getIndices(Orient orient){
    switch (orient)
    {
    case TOP:
        return array<pair<int,int>, 3>{make_pair(0, 0), make_pair(0, 1), make_pair(0, 2)};
    case RIGHT:
        return array<pair<int,int>, 3>{make_pair(0, 2), make_pair(1, 2), make_pair(2, 2)};
    case BOTTOM:
        return array<pair<int,int>, 3>{make_pair(2, 0), make_pair(2, 1), make_pair(2, 2)};
    case LEFT:
        return array<pair<int,int>, 3>{make_pair(0, 0), make_pair(1, 0), make_pair(2, 0)};
    default:
        throw std::runtime_error("Unknown orientation value");
    }
};

/**
 * @brief Class representing a single face of the rubics cube. It simply consists of a FaceArray storing the Color of each cell on the face, and a Color corresponding to the center.
 * 
 */
class RubeFace{
    public:
        Color FaceArray[3][3];
        enum Color center;

        /**
         * @brief Construct a new Rube Face object with no set Color
         * 
         */
        RubeFace(){
        }

        /**
         * @brief Construct a new Rube Face object with a set Color
         * 
         * @param color 
         */
        RubeFace(Color color){

            center = color;
            for (int i = 0; i < 3; i ++){
                for (int j = 0; j < 3; j ++){
                    FaceArray[i][j] = color;
                }
            }
        };

        /**
         * @brief Set the Color of this RubeFace
         * 
         * @param color 
         */
        void setColor(Color color){
            center = color;
            for (int i = 0; i < 3; i ++){
                for (int j = 0; j < 3; j ++){
                    FaceArray[i][j] = color;
                }
            }
        };

        /**
         * @brief Prints out the FaceArray as a 3 by 3 matrix 
         * 
         */
        void printFace(){
            for (int i = 0; i < 3; i ++){
                for (int j = 0; j < 3; j ++){
                    cout << this->FaceArray[0][0];
                    }
                cout << endl;
            }
        };
        
};

/**
 * @brief The class representing the rubics cube itself. It has an array of RubeFace objects representing each face. It also supports spatially valid rotations of each face.
 * 
 */
class RuboidCuboid{
    public:
        RubeFace rubeFaces[6];

        /**
         * @brief Construct a new RuboidCuboid object, with each face of a different color, in the correct order.
         * 
         */
        RuboidCuboid(){
            for (int i = 0; i < 6; i++){
                rubeFaces[i].setColor(Color(i));
            }
        };

        /**
         * @brief Rotates a given face of the cube either clockwise or counterclockwise.
         * 
         * @param face 
         * @param CCW 
         */
        void rotate(Color facecolor, bool CCW){
            if (CCW){
                // Replacing the corners of the current face
                RubeFace* face = &rubeFaces[facecolor];
                Color tl = face->FaceArray[0][0];
                // reset tl to bl
                face->FaceArray[0][0] = face->FaceArray[2][0];
                // reset bl to br
                face->FaceArray[2][0] = face->FaceArray[2][2];
                // reset br to tr
                face->FaceArray[2][2] = face->FaceArray[0][2];
                // reset tr to tl
                face->FaceArray[0][2] = tl;

                // Replacing the centers of the current face
                Color tc = face->FaceArray[0][1];
                // reset tc to lc
                face->FaceArray[0][1] = face->FaceArray[1][0];
                // reset lc to bc
                face->FaceArray[1][0] = face->FaceArray[2][1];
                // reset bc to rc
                face->FaceArray[2][1] = face->FaceArray[1][2];
                // reset rc to tc
                face->FaceArray[1][2] = tc;

                // Getting neighbor colors and neighbor orientations
                array<Color,4> neighborColors;
                array<Orient,4> neighborOrients;
                tie(neighborColors, neighborOrients) = getNeighbors(facecolor);

                RubeFace* prevface = new RubeFace();

                prevface = &rubeFaces[neighborColors[3]];
                Orient oriprev = neighborOrients[3];
                array<pair<int,int>, 3> indprev = getIndices(oriprev);
                array<Color, 3> prevtmpColors = array<Color, 3> {
                prevface->FaceArray[indprev[0].first][indprev[0].second],
                prevface->FaceArray[indprev[1].first][indprev[1].second],
                prevface->FaceArray[indprev[2].first][indprev[2].second]};

                for (int i = 0; i < 4; i++){
                    int iprev = (i+3)%4;

                    face = &rubeFaces[neighborColors[i]];
                    prevface = &rubeFaces[neighborColors[iprev]];

                    Orient ori = neighborOrients[i];
                    array<pair<int,int>, 3> ind = getIndices(ori);

                    array<Color, 3> tmpColors = array<Color, 3> {
                    face->FaceArray[ind[0].first][ind[0].second],
                    face->FaceArray[ind[1].first][ind[1].second],
                    face->FaceArray[ind[2].first][ind[2].second]};

                    for (int j = 0; j < 3; j++){
                        face->FaceArray[ind[j].first][ind[j].second] = prevtmpColors[j];
                    }
                    prevtmpColors = tmpColors;
                }
            }
            else{
                rotate(facecolor, true);
                rotate(facecolor, true);
                rotate(facecolor, true);
            }
        };

        /**
         * @brief prints out the cube's structure as a nice "spatially coherent" string.
         * 
         */
        void printCube(){
            int k = 0;
                for (int i = 0; i < 3; i++){
                    cout << "    ";
                    for (int j = 0; j < 3; j++){
                        cout << rubeFaces[k].FaceArray[i][j];
                    }
                    cout << endl;
                } 

            for (int i = 0; i < 3; i++){
                for (int k = 1; k < 5; k += 1){
                    for (int j = 0; j < 3; j++){
                        cout << rubeFaces[k].FaceArray[i][j];
                    }
                    cout << " ";
                } 
                cout << endl;
            }

            k = 5;
                for (int i = 0; i < 3; i++){
                    cout << "    ";
                    for (int j = 0; j < 3; j++){
                        cout << rubeFaces[k].FaceArray[i][j];
                    }
                    cout << endl;
                }
            cout << endl;
        };

};

int main()
{
    RuboidCuboid rubecube = RuboidCuboid();
    rubecube.printCube();

    rubecube.rotate(W,true);
    rubecube.rotate(G,true);
    rubecube.rotate(R,true);
    rubecube.rotate(Y,true);

    rubecube.printCube();

    rubecube.rotate(Y,false);
    rubecube.rotate(R,false);
    rubecube.rotate(G,false);
    rubecube.rotate(W,false);

    rubecube.printCube();
}