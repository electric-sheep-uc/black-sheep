package controller.ui.gameplay;

import common.TotalScaleLayout;
import controller.Clock;
import controller.ui.GCGUI;
import controller.ui.ui.customized.ImagePanel;
import data.Rules;
import data.communication.GameControlData;
import data.states.AdvancedData;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;


/**
 * @author Michel Bartsch
 * <p>
 * This is the main GUI.
 * In this class you will find the whole graphical output and the bindings
 * of buttons to their actions, nothing less and nothing more.
 */
public class GUI extends JFrame implements GCGUI, CommonGUI {
    public static final boolean IS_OSX = System.getProperty("os.name").contains("OS X");
    public static final boolean IS_APPLE_JAVA = IS_OSX && System.getProperty("java.version").compareTo("1.7") < 0;
    public static final Insets insets = IS_APPLE_JAVA ? new Insets(2, -30, 2, -30) : null;
    public static final String BUTTON_MASK = IS_APPLE_JAVA
            ? "<html><div style=\"padding: 0px 12px\"><center>%s</center></div></html>"
            : "<html><center>%s</center></html>";

    protected static final long serialVersionUID = 1L;

    /**
     * Some constants defining this GUI`s appearance as their names say.
     * Feel free to change them and see what happens.
     */
    protected static final int WINDOW_WIDTH = 1024;
    protected static final int WINDOW_HEIGHT = 768;
    protected static final String WINDOW_TITLE = "GameController";
    protected static final String ICONS_PATH = "config/icons/";

    protected static final String BACKGROUND_MID = "field.png";
    protected static final String STATE_INITIAL = "Initial";
    protected static final String CLOCK_RESET = "reset.png";
    protected static final String CLOCK_PAUSE = "pause.png";
    protected static final String CLOCK_PLAY = "play.png";
    protected static final String CLOCK_PLUS = "plus.png";
    protected static final String BACKGROUND_BOTTOM = "timeline_ground.png";
    public static final Color COLOR_HIGHLIGHT = Color.YELLOW;
    public static final int FINISH_HIGHLIGHT_SECONDS = 10;

    /**
     * Some attributes used in the GUI components.
     */
    protected ImageIcon clockImgReset;
    protected ImageIcon clockImgPlay;
    protected ImageIcon clockImgPause;
    protected ImageIcon clockImgPlus;
    protected ImageIcon[][] backgroundSide;

    /**
     * All the components of this GUI.
     */

    protected JPanel[] robots;

    protected JPanel mid;
    protected ImagePanel bottom;


    public GUI(boolean fullscreen, GameControlData data) {
        super(WINDOW_TITLE);
        setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        setResizable(true);

        GraphicsDevice gd = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice();
        int width = gd.getDisplayMode().getWidth();
        int height = gd.getDisplayMode().getHeight();
        setLocation((width - WINDOW_WIDTH) / 2, (height - WINDOW_HEIGHT) / 2);

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                Clock.getInstance().interrupt();
                dispose();
            }
        });

        clockImgReset = new ImageIcon(ICONS_PATH + CLOCK_RESET);
        clockImgPlay = new ImageIcon(ICONS_PATH + CLOCK_PLAY);
        clockImgPause = new ImageIcon(ICONS_PATH + CLOCK_PAUSE);
        clockImgPlus = new ImageIcon(ICONS_PATH + CLOCK_PLUS);

        backgroundSide = new ImageIcon[2][Rules.league.teamColor.length];

        for (int i = 0; i < Rules.league.backgroundSide.length; i++) {
            for (int j = 0; j < Rules.league.backgroundSide[i].length; j++) {
                backgroundSide[i][j] = new ImageIcon(ICONS_PATH + Rules.league.leagueDirectory + "/" + Rules.league.backgroundSide[i][j]);
            }
        }


        mid = new ImagePanel(new ImageIcon(ICONS_PATH + BACKGROUND_MID).getImage());
        bottom = new ImagePanel(new ImageIcon(ICONS_PATH + BACKGROUND_BOTTOM).getImage());

        //  robots
        robots = new JPanel[2];
        for (int i = 0; i < 2; i++) {
            robots[i] = new JPanel();
        }


        // TODO - move above stuff there
        setupGuiElement();

        // Setting up how the screen should look like
        setupLayout();

        //--listener--
        setupActionHandlers();


        //fullscreen
        if (fullscreen) {
            setUndecorated(true);
            GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice().setFullScreenWindow(this);
            if (IS_APPLE_JAVA) {
                setVisible(false); // without this, keyboard input is missing on OS X
            }
        }

        setVisible(true);
    }

    @Override
    public void setupGuiElement() {

    }

    public void setupLayout() {
        //--layout--
        TotalScaleLayout layout = new TotalScaleLayout(this);
        setLayout(layout);

        layout.add(.01, .21, .28, .55, robots[0]);
        layout.add(.71, .21, .28, .55, robots[1]);

        layout.add(.3, 0, .4, .87, mid);
        layout.add(0, .87, 1, .132, bottom);
    }

    @Override
    public void setupActionHandlers() {

    }

    @Override
    public void update(AdvancedData data) {
        repaint();
    }

    /**
     * Always update fonts before drawing.
     *
     * @param g The graphics context to draw to.
     */
    @Override
    public void paint(Graphics g) {
        //updateFonts();
        super.paint(g);
    }
}