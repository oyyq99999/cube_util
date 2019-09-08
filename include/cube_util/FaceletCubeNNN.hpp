#ifndef CUBE_UTIL_FACELETCUBENNN_HPP
#define CUBE_UTIL_FACELETCUBENNN_HPP

namespace cube_util {
    class FaceletCubeNNN {
        int size;
        int *facelets;

    public:
        FaceletCubeNNN(int size);

        int getSize() const;
        std::string prettify() const;
        friend std::ostream& operator<<(std::ostream& os, const FaceletCubeNNN &fc);

        void moveu(int layer, int amount);
        void mover(int layer, int amount);
        void movef(int layer, int amount);
        void moved(int layer, int amount);
        void movel(int layer, int amount);
        void moveb(int layer, int amount);
        void moveU(int amount);
        void moveR(int amount);
        void moveF(int amount);
        void moveD(int amount);
        void moveL(int amount);
        void moveB(int amount);
        void moveU();
        void moveR();
        void moveF();
        void moveD();
        void moveL();
        void moveB();
        void moveUw(int shift, int amount);
        void moveRw(int shift, int amount);
        void moveFw(int shift, int amount);
        void moveDw(int shift, int amount);
        void moveLw(int shift, int amount);
        void moveBw(int shift, int amount);
        void moveUw(int amount);
        void moveRw(int amount);
        void moveFw(int amount);
        void moveDw(int amount);
        void moveLw(int amount);
        void moveBw(int amount);

    };
}

#endif // CUBE_UTIL_FACELETCUBENNN_HPP
