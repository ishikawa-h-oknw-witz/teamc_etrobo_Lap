#include "ScenarioRunner.h"

void ScenarioRunner::run()
{
    // 赤ゲート攻略

    // 青ゲート攻略

    // 黄ゲート攻略
}

void ScenarioRunner::runGate(const GateInfo& gateInfo)
{
    // 目標基準点へ移動

    moveToBasePoint(gateInfo.basePointColor);

    // ゲート攻略

    executeRoute(gateInfo.gateNo);

    // 基準点へ帰還

    returnToBasePoint(gateInfo.basePointColor, gateInfo.gateNo);
}

void ScenarioRunner::moveToBasePoint(BasePointColor targetColor)
{
    // ライントレース開始

    // 指定色検知まで走行

    // 停止
}

void ScenarioRunner::executeRoute(int gateNo)
{
    switch(gateNo)
    {
        case 1:
            // 左端縦ゲート攻略
            break;

        case 2:
            // ゲート②攻略
            break;

        case 3:
            // ゲート③攻略
            break;

        default:
            break;
    }
}

void ScenarioRunner::returnToBasePoint(BasePointColor targetColor, int gateNo)
{
    // 基準線へ帰還

    // 基準点再検知
    switch(gateNo)
    {
        case 1:
            // 左端縦ゲート攻略
            break;

        case 2:
            // ゲート②攻略
            break;

        case 3:
            // ゲート③攻略
            break;

        default:
            break;
    }
}