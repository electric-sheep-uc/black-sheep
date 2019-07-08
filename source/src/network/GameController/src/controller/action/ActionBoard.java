package controller.action;

import controller.action.clock.ClockTick;
import controller.action.net.Manual;
import controller.action.ui.*;
import controller.action.ui.half.*;
import controller.action.ui.penalty.*;
import controller.action.ui.state.*;
import data.Rules;


/**
 * @author Michel Bartsch
 * <p>
 * This class actually holds static every instance of an action to get these
 * actions where ever you want to execute or identify them.
 * It may be usefull to have instances of actions that are not listed here,
 * that would be ok but for basic features it should not be needed.
 * Because of multi-thredding you should not take actions from here to write
 * into their attributes. However, you should allways avoid writing in
 * action`s attributes except in their constructor.
 * <p>
 * You can read a detailed description of each action in it`s class.
 */
public class ActionBoard {
    public static ClockTick clock;

    public static Quit quit;
    public static Testmode testmode;
    public static Undo[] undo;
    public static CancelUndo cancelUndo;
    public static final int MAX_NUM_UNDOS_AT_ONCE = 8;

    public static Goal[] goalDec = new Goal[2];
    public static Goal[] goalInc = new Goal[2];
    public static KickOff[] kickOff = new KickOff[2];
    public static Robot[][] robot;
    public static TimeOut[] timeOut = new TimeOut[2];
    public static GlobalStuck[] stuck = new GlobalStuck[2];
    public static Out[] out = new Out[2];
    public static ClockReset clockReset;
    public static ClockPause clockPause;
    public static IncGameClock incGameClock;
    public static FirstHalf firstHalf;
    public static SecondHalf secondHalf;
    public static FirstHalfOvertime firstHalfOvertime;
    public static SecondHalfOvertime secondHalfOvertime;
    public static PenaltyShoot penaltyShoot;
    public static RefereeTimeout refereeTimeout;
    public static Initial initial;
    public static Ready ready;
    public static Set set;
    public static Play play;
    public static Finish finish;
    public static BallManipulation ballManipulation;
    public static PickUpHL pickUpHL;
    public static TeammatePushing teammatePushing;
    public static Substitute substitute;
    public static DropBall dropBall;
    public static IndirectFreeKick[] indirectFreeKick = new IndirectFreeKick[2];
    public static DirectFreeKick[] directFreeKick = new DirectFreeKick[2];
    public static PenaltyKick[] penaltyKick = new PenaltyKick[2];
    public static CornerKick[] cornerKick = new CornerKick[2];
    public static GoalKick[] goalKick = new GoalKick[2];
    public static ThrowIn[] throwIn = new ThrowIn[2];

    public static Manual[][] manualPen = Rules.league.isCoachAvailable ? new Manual[2][Rules.league.teamSize + 1] : new Manual[2][Rules.league.teamSize];
    public static Manual[][] manualUnpen = Rules.league.isCoachAvailable ? new Manual[2][Rules.league.teamSize + 1] : new Manual[2][Rules.league.teamSize];


    /**
     * This must be called before using actions from this class. It creates
     * all the actions instances.
     */
    public static void init() {
        clock = new ClockTick();

        quit = new Quit();
        testmode = new Testmode();
        undo = new Undo[MAX_NUM_UNDOS_AT_ONCE];
        for (int i = 0; i < undo.length; i++) {
            undo[i] = new Undo(i);
        }
        cancelUndo = new CancelUndo();

        if (Rules.league.isCoachAvailable) {
            robot = new Robot[2][Rules.league.teamSize + 1];
        } else {
            robot = new Robot[2][Rules.league.teamSize];
        }

        for (int i = 0; i < 2; i++) {
            goalDec[i] = new Goal(i, -1);
            goalInc[i] = new Goal(i, 1);
            kickOff[i] = new KickOff(i);
            for (int j = 0; j < robot[i].length; j++) {
                robot[i][j] = new Robot(i, j);
            }
            timeOut[i] = new TimeOut(i);
            stuck[i] = new GlobalStuck(i);
            out[i] = new Out(i);
            indirectFreeKick[i] = new IndirectFreeKick(i);
            directFreeKick[i] = new DirectFreeKick(i);
            penaltyKick[i] = new PenaltyKick(i);
            cornerKick[i] = new CornerKick(i);
            goalKick[i] = new GoalKick(i);
            throwIn[i] = new ThrowIn(i);
        }

        clockReset = new ClockReset();
        clockPause = new ClockPause();
        incGameClock = new IncGameClock();
        firstHalf = new FirstHalf();
        secondHalf = new SecondHalf();
        firstHalfOvertime = new FirstHalfOvertime();
        secondHalfOvertime = new SecondHalfOvertime();
        penaltyShoot = new PenaltyShoot();
        refereeTimeout = new RefereeTimeout();

        initial = new Initial();
        ready = new Ready();
        set = new Set();
        play = new Play();
        finish = new Finish();

        ballManipulation = new BallManipulation();

        pickUpHL = new PickUpHL();
        teammatePushing = new TeammatePushing();
        substitute = new Substitute();
        dropBall = new DropBall();

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < Rules.league.teamSize; j++) {
                manualPen[i][j] = new Manual(i, j, false);
                manualUnpen[i][j] = new Manual(i, j, true);
            }
        }
    }
}