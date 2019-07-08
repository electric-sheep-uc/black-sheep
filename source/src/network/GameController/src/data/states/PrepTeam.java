package data.states;

import data.teams.TeamLoadInfo;
import data.values.TeamColors;

/**
 * Created by rkessler on 2017-02-11.
 */
public class PrepTeam {

    private TeamLoadInfo teamLoadInfo;
    private String teamColor;

    private PrepTeam(TeamLoadInfo teamLoadInfo, String color){
        this.teamLoadInfo = teamLoadInfo;
        teamColor = color;
    }

    public PrepTeam(TeamLoadInfo teamLoadInfo){
        this.teamLoadInfo = teamLoadInfo;

        if (teamLoadInfo.colors == null || teamLoadInfo.colors.length == 0){
            this.teamColor = "Blue";
        } else {
            this.teamColor = teamLoadInfo.colors[0];
        }
    }

    public String getTeamColor() {
        return teamColor;
    }

    public TeamColors getTeamColorAsByte() {
        // TODO Go all the way and implement the TeamColor Enum here as well
        return TeamColors.fromColorName(teamColor.toLowerCase());
    }

    public void setTeamColor(String teamColorString) {
        this.teamColor = teamColorString;
    }

    public PrepTeam clone(){
        return new PrepTeam(this.teamLoadInfo, this.teamColor);
    }

    public TeamLoadInfo getTeamInfo() {
        return teamLoadInfo;
    }

    public String toString(){
        return String.format("%s %s", teamLoadInfo, teamColor);
    }

    public void cycleColours() {
        String[] available_colors = this.teamLoadInfo.colors;
        if (available_colors == null || available_colors.length == 0){
            available_colors = new String[]{"Blue", "Red"};
        }

        // Find the currently active color
        int i;
        for(i = 0; i < available_colors.length; i++){
            if(available_colors[i].equals(this.teamColor)){
                break;
            }
        }
        this.teamColor = available_colors[(i+1) % available_colors.length];
    }
}