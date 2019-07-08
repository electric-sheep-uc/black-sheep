package data.states;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;

import common.Log;
import controller.action.ActionBoard;
import data.PlayerInfo;
import data.Rules;
import data.spl.SPLCoachMessage;
import data.communication.TeamInfo;
import data.communication.GameControlData;
import data.values.*;

/**
 * This class extends the GameControlData that is send to the robots. It
 * contains all the additional informations the GameControler needs to
 * represent a state of the game, for example time in millis.
 * 
 * There are no synchronized get and set methods because in this architecture
 * only actions in their perform method are allowed to write into this and they
 * are all in the same thread. Look in the EventHandler for more information.
 * 
 * @author Michel Bartsch
 * @author Dennis Schürholz (bhuman@dennisschuerholz.de)
 */
public class AdvancedData extends GameControlData implements Cloneable
{
    private static final long serialVersionUID = 2720243434306304319L;

    /** This message is set when the data is put into the timeline */
    public String message = "";

    /** Indicates whether the side assignment is the same as from the game start (true) or flipped (false) */
    public boolean sides_as_started = true;

    /** How much time summed up before the current state? (ms)*/
    public long timeBeforeCurrentGameState;
    
    /** When was switched to the current state? (ms) */
    public long whenCurrentGameStateBegan;
    
    /** How long ago started the current game state? (ms) Only set when written to log! */
    public long timeSinceCurrentGameStateBegan;

    /** When was the last drop-in? (ms, 0 = never) */
    public long whenDropIn;

    /** The Game Clock object that can be stopped, paused, etc. **/
    public GameClock gameClock;
    
    /** When was each player penalized last (ms, 0 = never)? */
    public long[][] whenPenalized = Rules.league.isCoachAvailable ? new long[2][Rules.league.teamSize+1] : new long[2][Rules.league.teamSize];

    /** Is a player currently serving a penalty */
    public boolean[][] isServingPenalty = Rules.league.isCoachAvailable ? new boolean[2][Rules.league.teamSize+1] : new boolean[2][Rules.league.teamSize];

    /** How often was each team penalized? */
    public int[] penaltyCount = new int[2];

    /** How often was each team penalized at before the robot got penalized? */
    public int[][] robotPenaltyCount = new int[2][Rules.league.teamSize];

    /** Which players were already ejected? */
    public boolean [][] ejected = Rules.league.isCoachAvailable ? new boolean[2][Rules.league.teamSize+1] : new boolean[2][Rules.league.teamSize];
    
    /** Pushing counters for each team, 0:left side, 1:right side. */
    public int[] pushes = {0, 0};
    
    /** If true, the referee set a timeout */
    public boolean refereeTimeout = false;

    /** If true, this team is currently taking a timeOut, 0:left side, 1:right side. */
    public boolean[] timeOutActive = {false, false};
    
    /** TimeOut counters for each team, 0:left side, 1:right side. */
    public boolean[] timeOutTaken = {false, false};

    /** Whether we are in the penalty kick mode */
    public boolean[] penaltyKickActive = {false, false};

    /** If true, left side has the kickoff. */
    public boolean leftSideKickoff = true;
    
    /** If true, the colors change automatically. */
    public boolean colorChangeAuto;
    
    /** If true, the testmode has been activated. */
    public boolean testmode = false;

    /** If true, the clock has manually been paused in the testmode. */
    public boolean manPause = false;
    
    /** If true, the clock has manually been started in the testmode. */
    public boolean manPlay = false;
    
    /** When was the last manual intervention to the clock? */
    public long manWhenClockChanged;
    
    /** Time offset resulting from manually stopping the clock. */
    public long manTimeOffset;
    
    /** Time offset resulting from starting the clock when it should be stopped. */
    public long manRemainingGameTimeOffset;

    /** Used to backup the secondary game state during a timeout. */
    public SecondaryGameStates previousSecGameState = SecondaryGameStates.NORMAL;

    public static final byte KICKOFF_HALF = 0;
    public static final byte KICKOFF_TIMEOUT = 1;
    public static final byte KICKOFF_GAMESTUCK = 2;
    public static final byte KICKOFF_PENALTYSHOOT = 3;
    public static final byte KICKOFF_GOAL = 4;
    public byte kickOffReason = KICKOFF_HALF;

    /** Keeps the penalties for the players if there are substituted */
    public ArrayList<ArrayList<PenaltyQueueData>> penaltyQueueForSubPlayers = new ArrayList<ArrayList<PenaltyQueueData>>();

    /** Keep the timestamp when a coach message was received*/
    public long timestampCoachPackage[] = {0, 0};

    /** Keep the coach messages*/
    public  ArrayList<SPLCoachMessage> splCoachMessageQueue = new ArrayList<SPLCoachMessage>();

    /**
     * Creates a new AdvancedData.
     */
    public AdvancedData()
    {
        if (Rules.league.startWithPenalty) {
            secGameState = SecondaryGameStates.PENALTYSHOOT;
        }
        for (int i=0; i<2; i++) {
            for (int j=0; j < team[i].player.length; j++) {
                if (j >= Rules.league.robotsPlaying) {
                    team[i].player[j].penalty = Penalties.SUBSTITUTE;
                }
            }
            penaltyQueueForSubPlayers.add(new ArrayList<PenaltyQueueData>());
        }

        gameClock = new GameClock();
    }

    /**
     * Generically clone this object. Everything referenced must be Serializable.
     * @return A deep copy of this object.
     */
    public Object clone()
    {
        try {
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            new ObjectOutputStream(out).writeObject(this);
            ByteArrayInputStream in = new ByteArrayInputStream(out.toByteArray());
            return new ObjectInputStream(in).readObject();
        } catch (ClassNotFoundException e) {
            System.out.println(e.getClass().getName() + ": " + e.getMessage());
        } catch (IOException e) {
            System.out.println(e.getClass().getName() + ": " + e.getMessage());
        }
        return null; // Should never be reached
    }
    
    /**
     * Returns the side on which a team plays. The team should be playing
     * via this GameController.
     * 
     * @param teamNumber    The unique teamNumber.
     * 
     * @return The side of the team, 0:left side, 1:right side.
     */
    public int getSide(short teamNumber)
    {
        return teamNumber == team[0].teamNumber ? 0 : 1;
    }
    
    /**
     * Returns the current time. Can be stopped in test mode.
     * @return The current time in ms. May become incompatible to
     *         the time delivered by System.currentTimeMillis().
     */
    public long getTime()
    {
        return manPause ? manWhenClockChanged : System.currentTimeMillis() + manTimeOffset;
    }
    
    /**
     * Returns the number of seconds since a certain timestamp.
     * @param millis The timestamp in ms.
     * @return The number of seconds since the timestamp.
     */
    public int getSecondsSince(long millis) {
        return millis == 0 ? 100000 : (int) (getTime() - millis) / 1000;
    }
    
    /**
     * The number of seconds until a certion duration is over. The time
     * already passed is specified as a timestamp when it began.
     * @param millis The timestamp in ms.
     * @param durationInSeconds The full duration in s.
     */
    public int getRemainingSeconds(long millis, int durationInSeconds) {
        return durationInSeconds - getSecondsSince(millis);
    }

    public void setManualPause(boolean value){
        manPause = value;
    }

    /**
     * Update all durations in the GameControlData packet.
     */
    public void updateTimes()
    {
        secsRemaining = (short) getRemainingGameTime(false);
        dropInTime = whenDropIn == 0 ? -1 : (short) getSecondsSince(whenDropIn);
        Integer subT = getSecondaryTime(0);

        if (subT == null) {
            secondaryTime = 0;
        } else {
            secondaryTime = (short)(int)subT;
        }
        for (int side = 0; side < team.length; ++side) {
            for (int number = 0; number < team[side].player.length; ++number) {
                PlayerInfo player = team[side].player[number];
                if (player.penalty == Penalties.NONE) {
                    player.secsTillUnpenalised = 0;
                } else {
                    player.secsTillUnpenalised = (byte)getRemainingPenaltyTime(side, number);
                    // Auto-remove penalties once robots have served penalty time
                    if (player.penalty != Penalties.NONE && player.secsTillUnpenalised == 0 &&
                            player.penalty != Penalties.MANUAL && player.penalty != Penalties.SUBSTITUTE) {
                        player.penalty = Penalties.NONE;
                    }
                }
            }
        }
    }
    
    /**
     * Add the time passed in the current game state to the time that already passed before.
     * Is usually called during changes of the game state.
     */
    public void addTimeInCurrentState()
    {
        timeBeforeCurrentGameState += getTime() - whenCurrentGameStateBegan;
    }
    
    /**
     * Calculates the remaining game time in the current phase of the game.
     * This is what the primary clock will show.
     * @param real If true, the real time will be returned. If false, the first number of seconds in the playing state
     *             in play-off games will not be updated.
     * @return The remaining number of seconds.
     */
    public int getRemainingGameTime(boolean real)
    {
        int regularNumberOfPenaltyShots = (gameType == GameTypes.PLAYOFF) ? Rules.league.numberOfPenaltyShotsLong : Rules.league.numberOfPenaltyShotsShort;
        int duration = secGameState == SecondaryGameStates.TIMEOUT ? secsRemaining :
                secGameState == SecondaryGameStates.NORMAL ? Rules.league.halfTime :
                secGameState.isGameInterruption() ? secsRemaining
                : secGameState == SecondaryGameStates.OVERTIME ? Rules.league.overtimeTime
                : Math.max(team[0].penaltyShot, team[1].penaltyShot) > regularNumberOfPenaltyShots
                ? Rules.league.penaltyShotTimeSuddenDeath
                : Rules.league.penaltyShotTime;
        int timePlayed = gameState == GameStates.INITIAL// during timeouts
                || (gameState == GameStates.READY || gameState == GameStates.SET)
                && ((gameType == GameTypes.PLAYOFF) && Rules.league.playOffTimeStop || timeBeforeCurrentGameState == 0)
                || gameState == GameStates.FINISHED
                ? (int) ((timeBeforeCurrentGameState + manRemainingGameTimeOffset + (manPlay ? System.currentTimeMillis() - manWhenClockChanged : 0)) / 1000)
                : real || (gameType != GameTypes.PLAYOFF && timeBeforeCurrentGameState > 0) || secGameState != SecondaryGameStates.NORMAL || gameState != GameStates.PLAYING
                || getSecondsSince(whenCurrentGameStateBegan) >= Rules.league.delayedSwitchToPlaying 
                ? getSecondsSince(whenCurrentGameStateBegan - timeBeforeCurrentGameState - manRemainingGameTimeOffset)
                : (int) ((timeBeforeCurrentGameState - manRemainingGameTimeOffset) / 1000);
        return duration - timePlayed;
    }
    
    /**
     * The method returns the remaining pause time.
     * @return The remaining number of seconds of the game pause or null if there currently is no pause.
     */
    public Integer getRemainingPauseTime()
    {
        if (secGameState == SecondaryGameStates.NORMAL
                && (gameState == GameStates.INITIAL && firstHalf != C_TRUE && !timeOutActive[0] && !timeOutActive[1]
                || gameState == GameStates.FINISHED && firstHalf == C_TRUE)) {
            return getRemainingSeconds(whenCurrentGameStateBegan, Rules.league.pauseTime);
        } else if (Rules.league.pausePenaltyShootOutTime != 0 && (gameType == GameTypes.PLAYOFF) && team[0].score == team[1].score
                && (gameState == GameStates.INITIAL && secGameState == SecondaryGameStates.PENALTYSHOOT && !timeOutActive[0] && !timeOutActive[1]
                || gameState == GameStates.FINISHED && firstHalf != C_TRUE)) {
            return getRemainingSeconds(whenCurrentGameStateBegan, Rules.league.pausePenaltyShootOutTime);
        } else {
            return null;
        }
    }
    
    /**
     * Resets the penalize time of all players to 0.
     * This does not unpenalize them.
     */
    public void resetPenaltyTimes()
    {
        for (long[] players : whenPenalized) {
            for (int i = 0; i < players.length; ++i) {
                players[i] = 0;
            }
        }
    }
    
    /**
     * Resets all penalties.
     */
    public void resetPenalties()
    {
        for (int i = 0; i < team.length; ++i) {
            pushes[i] = 0;
            for (int j = 0; j < Rules.league.teamSize; j++) {
                if (!ActionBoard.robot[i][j].isCoach(this) && team[i].player[j].penalty != Penalties.SUBSTITUTE) {
                    team[i].player[j].penalty = Penalties.NONE;
                    if (Rules.league.resetEjectedRobotsOnHalftime) {
                        ejected[i][j] = false;
                    }
                }
                if (Rules.league.resetPenaltyCountOnHalftime) {
                    robotPenaltyCount[i][j] = 0;
                }
            }
            if (Rules.league.resetPenaltyCountOnHalftime) {
                penaltyCount[i] = 0;
            }
        }
        resetPenaltyTimes();
        for (int i = 0; i < 2; i++) {
            penaltyQueueForSubPlayers.get(i).clear();
        }
    }
    
    /**
     * Calculates the remaining time a certain robot has to stay penalized.
     * @param side 0 or 1 depending on whether the robot's team is shown left or right.
     * @param number The robot's number starting with 0.
     * @return The number of seconds the robot has to stay penalized, 0 in case Penalty is manual or substitute
     */
    public int getRemainingPenaltyTime(int side, int number)
    {
        Penalties penalty = team[side].player[number].penalty;
        int penaltyTime = -1;
        if (penalty != Penalties.MANUAL && penalty != Penalties.SUBSTITUTE) {
            penaltyTime = penalty.penaltyTime() + Rules.league.penaltyIncreaseTime * robotPenaltyCount[side][number];
        }
        assert penalty == Penalties.MANUAL || penalty == Penalties.SUBSTITUTE || penaltyTime != -1;
        if (penalty == Penalties.MANUAL || penalty == Penalties.SUBSTITUTE) {
            return 0;
        }
        else if (!isServingPenalty[side][number]) {// If robot has not started serving the penalty time, remaining time is fixed
            return penaltyTime;
        }
        else if (gameState == GameStates.READY && Rules.league.returnRobotsInGameStoppages && whenPenalized[side][number] >= whenCurrentGameStateBegan) {
            return Rules.league.readyTime - getSecondsSince(whenCurrentGameStateBegan);
        }
        return Math.max(0, getRemainingSeconds(whenPenalized[side][number], penaltyTime));
    }
    
    /**
     * Calculates the Number of robots in play (not substitute) on one side
     * @param side 0 or 1 depending on whether the team is shown left or right.
     * @return The number of robots without substitute penalty on the side
     */
    public int getNumberOfRobotsInPlay(int side)
    {
        int count = 0;
        for (int i=0; i<team[side].player.length; i++) {
            if (team[side].player[i].penalty != Penalties.SUBSTITUTE) {
                count++;
            }
        }
        return count;
    }
    
    /**
     * Determines the secondary time. Although this is a GUI feature, the secondary time
     * will also be encoded in the network packet.
     * @param timeKickOffBlockedOvertime In case the kickOffBlocked time is delivered, this
     *                                   parameter specified how long negative values will
     *                                   be returned before the time is switched off.
     * @return The secondary time in seconds or null if there currently is none.
     */
    public Integer getSecondaryTime(int timeKickOffBlockedOvertime)
    {

        if (secGameState.isGameInterruption()) {
            return gameClock.getSecondaryTime();
        }

        if(timeKickOffBlockedOvertime == 0 // preparing data packet
                && secGameState == SecondaryGameStates.NORMAL && gameState == GameStates.PLAYING
                && getSecondsSince(whenCurrentGameStateBegan) < Rules.league.delayedSwitchToPlaying) {
            return null;
        }
        int timeKickOffBlocked = getRemainingSeconds(whenCurrentGameStateBegan, Rules.league.kickoffTime);
        if (kickOffTeam == DROPBALL) {
            timeKickOffBlocked = 0;
        }
        if (gameState == GameStates.INITIAL && (timeOutActive[0] || timeOutActive[1])) {
            return getRemainingSeconds(whenCurrentGameStateBegan, Rules.league.timeOutTime);
        }
        else if (gameState == GameStates.INITIAL && (refereeTimeout)) {
            return getRemainingSeconds(whenCurrentGameStateBegan, Rules.league.refereeTimeout);
        }
        else if (gameState == GameStates.READY) {
            return getRemainingSeconds(whenCurrentGameStateBegan, Rules.league.readyTime);
        } else if (gameState == GameStates.PLAYING && secGameState != SecondaryGameStates.PENALTYSHOOT
                && timeKickOffBlocked >= -timeKickOffBlockedOvertime) {
            if (timeKickOffBlocked > 0) {
                return timeKickOffBlocked;
            } else {
                return null;
            }
        } else {
            return getRemainingPauseTime();
        }
    }

    /**
     * Dispatch the coach messages. Since coach messages are texts, the messages are zeroed
     * after the first zero character, to avoid the transport of information the
     * GameStateVisualizer would not show.
     */
    public void updateCoachMessages()
    {
        int i = 0;
        while (i < splCoachMessageQueue.size()) {
            if (splCoachMessageQueue.get(i).getRemainingTimeToSend() == 0) {
                for (int j = 0; j < 2; j++) {
                    if (team[j].teamNumber == splCoachMessageQueue.get(i).team) {
                        byte[] message = splCoachMessageQueue.get(i).message;
                        
                        // All chars after the first zero are zeroed, too
                        int k = 0;
                        while (k < message.length && message[k] != 0) {
                            k++;
                        }
                        while (k < message.length) {
                            message[k++] = 0;
                        }
                        
                        team[j].coachSequence = splCoachMessageQueue.get(i).sequence;
                        team[j].coachMessage = message;
                        Log.toFile("Coach Message Team "+ team[j].teamColor.toString() + " " + new String(message));
                        splCoachMessageQueue.remove(i);
                        break;
                    }
                }
            } else {
                i++;
            }
        }
    }
    
    public void updatePenalties() {
        for (TeamInfo t : team) {
            for (PlayerInfo p : t.player) {
            }
        }
    }

    public TeamInfo getTeam(Side side) {
        return team[side.value()];
    }

    public class PenaltyQueueData  implements Serializable {
        private static final long serialVersionUID = 7536004813202642582L;

        public long whenPenalized;
        public Penalties penalty;
        public int penaltyCount;

        public PenaltyQueueData(long whenPenalized, Penalties penalty, int penaltyCount) {
            this.whenPenalized = whenPenalized;
            this.penalty = penalty;
            this.penaltyCount = penaltyCount;
        }
    }

    public void addToPenaltyQueue(int side, long whenPenalized, Penalties penalty, int penaltyCount) {
        penaltyQueueForSubPlayers.get(side).add(new PenaltyQueueData(whenPenalized, penalty, penaltyCount));
    }


    public void changeSide()
    {
        // TODO fix quick
        AdvancedData data = this;
        TeamInfo team = data.team[0];
        data.team[0] = data.team[1];
        data.team[1] = team;
        boolean[] ejected = data.ejected[0];
        data.ejected[0] = data.ejected[1];
        data.ejected[1] = ejected;
        // if necessary, swap back team colors
        if (data.secGameState != SecondaryGameStates.PENALTYSHOOT
                && data.colorChangeAuto) {
            TeamColors color = data.team[0].teamColor;
            data.team[0].teamColor = data.team[1].teamColor;
            data.team[1].teamColor = color;
        }

        if (Rules.league.timeOutPerHalf && (data.secGameState != SecondaryGameStates.PENALTYSHOOT)) {
            data.timeOutTaken = new boolean[] {false, false};
        } else {
            boolean timeOutTaken = data.timeOutTaken[0];
            data.timeOutTaken[0] = data.timeOutTaken[1];
            data.timeOutTaken[1] = timeOutTaken;
        }

        data.timeBeforeCurrentGameState = 0;
        data.whenDropIn = 0;
        if(data.secGameState != SecondaryGameStates.PENALTYSHOOT) {
            data.resetPenalties();
        }

        sides_as_started = !sides_as_started;
    }

    public boolean isSecondaryClockLowerThan(Integer value){
        return getSecondaryTime(0) <= value || gameClock.isSecondaryClockLowerThan(value);

    }

}