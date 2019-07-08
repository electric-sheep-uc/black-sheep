package controller.ui.ui.customized;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

/**
 * Created by rkessler on 2017-03-28.
 */
public class BestFitImagePanel extends ImagePanel
{
    protected static final long serialVersionUID = 1L;

    /** The image that is shown in the background. */
    protected Image image;

    /**
     * Creates a new ImagePanel.
     *
     * @param image The Image to be shown in the background.
     */
    public BestFitImagePanel(Image image) {
        super(image);
    }

    public void setImage(Image image)
    {
        this.image = image;
        this.rescale();
    }


    private void rescale(){
        int new_width = (int) (this.getHeight() * ((double) image.getWidth(null) / image.getHeight(null)));
        image = image.getScaledInstance(new_width, this.getHeight(), 1);
    }

    @Override
    public void paintComponent(Graphics g)
    {
        if (super.isOpaque()) {
            Color color = UIManager.getColor ( "Panel.background" );
            g.setColor(color);
            g.fillRect(0, 0, getWidth(), getHeight());
        }

        if (image != null) {
            int offset = getWidth() - image.getWidth(null);
            g.drawImage(image, offset/2, 0, image.getWidth(null), image.getHeight(null), null);
        }
    }
}


