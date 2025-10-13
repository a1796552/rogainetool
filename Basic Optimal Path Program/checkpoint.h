#ifndef CHECKPOINT_H
#define CHECKPOINT_H

/* Class to keep track of individual checkpoints with their x and y coordinates */
class checkpoint {
    private:
        int checkpointID;
        double x;
        double y;
        int value;
        bool visited = false;
    public:
        checkpoint(int id, double x, double y, int value);

        friend class routePlanner;
};

#endif