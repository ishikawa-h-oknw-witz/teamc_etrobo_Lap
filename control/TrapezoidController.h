using namespace Controll{

    class TrapezoidController { 
        public:
        TrapezoidController(spikeapi::Clock clock);
        void startControll();
        int getControllValue();

        private:
        int time;
        int startValue;
        int maxValue;
        int stopValue;
        int maxslope;

    }
}