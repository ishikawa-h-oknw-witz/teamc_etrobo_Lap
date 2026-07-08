using namespace State{

class RallyStateManager
{
    private:
    int RoundCount;
    GateInfo TargetGate;
    RallyState currentState;

public:
    RallyStateManager(int roundCount, const GateInfo& targetGate, RallyState initialState): 
    RoundCount(roundCount),
    TargetGate(targetGate),
    currentState(initialState){};
    
    ~RallyStateManager();  //デコンストラクタ 消してもいい

    void Update(float deltaTime);
    RallyState GetRallyState() const;
}

struct GateInfo
{
    BasePointColor Area;    //基準点色
    int PositionID;         //通過点番号
};

enum class BasePointColor  //基準点の色を区間のIDとして1対1対応させている
{
    Red,
    Blue,
    Green,
    Yellow
};

enum class RallyState
{
    OnBaseLine,  //基準線ライントレース状態
/*基準点到着で遷移*/
    AtBasePoint,  //基準点からゲート突入までの位置調整状態？いらないかも
/*走行体が基準線に垂直になったら遷移*/
    Going,  //ゲートにむかってシナリオ走行中状態
/*シナリオ完遂時遷移*/
    Returning,  //シナリオで帰還状態
/*基準点到着で遷移*/
    UntilBaseLine  //基準点から基準線に移行状態．OnBaseLineに移る

};
}