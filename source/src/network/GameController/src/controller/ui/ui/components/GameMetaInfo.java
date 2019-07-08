package controller.ui.ui.components;

import common.TotalScaleLayout;
import controller.ui.helper.FontHelper;
import controller.ui.ui.customized.BestFitImagePanel;
import controller.ui.ui.customized.ImagePanel;
import data.Rules;
import data.communication.TeamInfo;
import data.states.AdvancedData;
import data.states.GamePreparationData;
import data.teams.TeamLoadInfo;
import data.teams.TeamsLoader;
import data.values.Side;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.util.Map;


/**
 * Created by rkessler on 2017-07-21.
 */
public class GameMetaInfo extends AbstractComponent {

    private JPanel container;

    private JLabel left_team;
    private JLabel right_team;

    private BestFitImagePanel left_team_logo;
    private BestFitImagePanel right_team_logo;

    private Map<Integer, TeamLoadInfo> teamLoadInfoMap;

    private JLabel score_label;


    public GameMetaInfo(AdvancedData initialData, GamePreparationData gamePrepData) {
        teamLoadInfoMap = TeamsLoader.getInstance().getTeamLoadInfoMap(gamePrepData.getCurrentRules().leagueName);

        TeamInfo ti = initialData.getTeam(Side.LEFT);
        left_team = new JLabel(ti.getName());
        left_team.setFont(FontHelper.boldHeadlineFont());
        left_team.setHorizontalAlignment(SwingConstants.CENTER);
        left_team.setVerticalAlignment(SwingConstants.CENTER);
        left_team.setBackground(ti.teamColor.colorValue());
        left_team.setOpaque(true);

        TeamInfo ti2 = initialData.getTeam(Side.RIGHT);
        right_team = new JLabel(ti2.getName());
        right_team.setFont(FontHelper.boldHeadlineFont());
        right_team.setHorizontalAlignment(SwingConstants.CENTER);
        right_team.setVerticalAlignment(SwingConstants.CENTER);
        right_team.setBackground(ti2.teamColor.colorValue());
        right_team.setOpaque(true);

        score_label = new JLabel("0 - 0");
        score_label.setFont(FontHelper.boldHeadlineFont());
        score_label.setHorizontalAlignment(SwingConstants.CENTER);
        score_label.setVerticalAlignment(SwingConstants.CENTER);

        left_team_logo = new BestFitImagePanel(null);
        right_team_logo = new BestFitImagePanel(null);


        defineLayout();
    }


    protected void defineLayout() {
        container = new JPanel();
        TotalScaleLayout layout = new TotalScaleLayout(container);

        container.setLayout(layout);
        layout.add(0, 0, 0.28, 1, left_team);
        layout.add(0.28, 0, 0.17, 1, left_team_logo);
        layout.add(0.45, 0, 0.10, 1, score_label);
        layout.add(0.55, 0, 0.17, 1, right_team_logo);
        layout.add(0.72, 0, 0.28, 1, right_team);

        //container.setSize(100, 100);
        container.setVisible(true);


        this.setLayout(new TotalScaleLayout(this));
        ((TotalScaleLayout) this.getLayout()).add(0, 0, 1, 1, container);
        this.setVisible(true);
    }



    public void update(AdvancedData data) {
        TeamInfo right_team_info = data.team[Side.RIGHT.value()];
        TeamInfo left_team_info = data.team[Side.LEFT.value()];

        String left = String.valueOf(left_team_info.score);
        String right = String.valueOf(right_team_info.score);
        score_label.setText(left + " - " + right);


        left_team.setText(left_team_info.getName());
        left_team.setBackground(left_team_info.teamColor.colorValue());

        BufferedImage left_team_image = teamLoadInfoMap.get((int) left_team_info.teamNumber).icon;
        this.left_team_logo.setImage(left_team_image);

        this.right_team.setText(right_team_info.getName());
        this.right_team.setBackground(right_team_info.teamColor.colorValue());

        BufferedImage right_team_image = teamLoadInfoMap.get((int) right_team_info.teamNumber).icon;
        this.right_team_logo.setImage(right_team_image);
    }
}
