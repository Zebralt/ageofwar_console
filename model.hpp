#ifndef model_hpp__
#define model_hpp__

#include <string>

    class Model {
    protected:
        std::string name;
        int maxHP = 10;
        int price = 0;

    public:

        friend class Unit;

        Model(std::string name, int maxHP, int price);

        int getMaxHealth();

        virtual ~Model() {}
    };

    class HostileModel : public virtual Model {
        protected:

            int attackScore = 1;
            int range = 1;          // portée maximale
            int exclusiveRange = 0; // portée minimale
            int trample = 0;        // aea of effect

        public:
            friend class HostileUnit;
            HostileModel(std::string name, int maxHP, int price, int attackScore, int range, int exclusiveRange);

            ~HostileModel()  {}
    };


    class MobileModel : public virtual Model {
        private:
            int speed = 0;
        public:

            friend class MobileUnit;

            MobileModel(std::string name, int maxHP, int price, int attackScore, int range, int exclusiveRange, int speed);

            void setSpeed(int);
            int getSpeed();

            ~MobileModel() {}
    };

#endif
