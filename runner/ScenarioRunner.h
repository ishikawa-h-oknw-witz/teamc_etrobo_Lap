#ifndef SCENARIO_RUNNER_H
#define SCENARIO_RUNNER_H

class ScenarioRunner
{
public:

    /**
     * ETラリー1周実行
     */
    void run();

    /**
     * 指定ゲート攻略
     */
    void runGate(const GateInfo& gateInfo);

private:

    /**
     * 基準点まで移動
     */
    void moveToBasePoint(BasePointColor targetColor);

    /**
     * ゲート攻略経路実行
     */
    void executeRoute(int gateNo);

    /**
     * 基準点へ帰還
     */
    void returnToBasePoint(BasePointColor targetColor, int gateNo);

private:

    LineTracer& mLintracer
    BasePointDetector& mBasePointDetector
    DirectionController& mDirectionController;
};
#endif