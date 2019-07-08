package data.hl;

/**
 * This class sets attributes given by the humanoid-league rules.
 *
 * @author Michel-Zen
 */
public class HLAdult extends HL
{
    public HLAdult()
    {
        /** The league´s name this rules are for. */
        leagueName = "HL Adult";
        /** The league´s directory name with it´s teams and icons. */
        leagueDirectory = "hl_adult";
        /** How many robots are in a team. */
        teamSize = 4;
        /** How many robots of each team may play at one time. */
        robotsPlaying = 2;
    }
}
