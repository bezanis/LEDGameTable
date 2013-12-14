import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import javax.swing.*;

public class MazeLevelEditor extends Component {
	private static final long serialVersionUID = 1L;
	private static final int START_COLOR = 0xFF0000FF;
	private static final int END_COLOR = 0xFF00FF00;
	BufferedImage img;

	public void paint(Graphics g) {
		g.drawImage(img, 0, 0, null);
	}

	public MazeLevelEditor() {
		try {
			Point startPos = null;
			Point endPos = null;
			int printCount=0;
			img = ImageIO.read(new File("level2.png"));
			for (int x = 0; x < img.getWidth(); x++) {
				for (int y = 0; y < img.getHeight(); y++) {
					if (img.getRGB(x, y) == START_COLOR) {
						startPos = new Point(x,y);
					}else if (img.getRGB(x, y) == END_COLOR) {
						endPos = new Point(x,y);
					}
				}
			}
			if(startPos==null){
				System.out.println("Start pos is null");
			}else if(endPos==null){
				System.out.println("End pos is null");
			}else{
				System.out.print(((endPos.y-startPos.y)*(-1))+","+(endPos.x-startPos.x)+", ");
				for (int x = 0; x < img.getWidth(); x++) {
					for (int y = 0; y < img.getHeight(); y++) {
						if (img.getRGB(x, y) == -1) {
							printCount++;
							if(printCount%10==0){
								System.out.print("\r\t");
							}
							System.out.print(((-1)*(y-startPos.y))+","+(x-startPos.x)+", ");
						}
					}
				}
			}
			System.out.print("\rElements: "+(printCount+1));
		} catch (IOException e) {
		}
	}

	public Dimension getPreferredSize() {
		if (img == null) {
			return new Dimension(100, 100);
		} else {
			return new Dimension(img.getWidth(null), img.getHeight(null));
		}
	}

	public static void main(String[] args) {
		JFrame f = new JFrame("Loaded Level");
		f.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		f.add(new MazeLevelEditor());
		f.pack();
		f.setVisible(true);
	}
}