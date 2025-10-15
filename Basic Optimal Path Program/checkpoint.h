#ifndef CHECKPOINT_H
#define CHECKPOINT_H

/* Class to keep track of individual checkpoints with their x and y coordinates */
class checkpoint {
    private:
        int checkpointID;
        double x;
        double y;
        int value;
    public:
        checkpoint(int id, double x, double y);
        double getX(){return x;}
        double getY(){return y;}
        int getID(){return checkpointID;}
        int getValue(){return value;}
        friend class routePlanner;
};

#endif