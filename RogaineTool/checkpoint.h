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
        double getX() const {return x;}
        double getY() const {return y;}
        int getID() const {return checkpointID;}
        int getValue() const {return value;}
        friend class routePlanner;
};

#endif