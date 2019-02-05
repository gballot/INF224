import java.awt.*;
import java.awt.event.ActionEvent;
import javax.swing.*;

public class RequestWindow extends JFrame {
  private JPanel container = new JPanel();
  private JTextField jtfs[];
  private JLabel labels[];
  private JButton b = new JButton ("OK");
  private Client client;
  private MainWindow window;
  private int n;

  public RequestWindow(String request, String[] man, Client client, MainWindow window){
    n = man.length;
	this.client = client;
	this.window = window;
    this.setTitle("Request to C++ server");
    this.setSize(300, n*100);
    this.setLocationRelativeTo(null);
    container.setLayout(new BorderLayout());
    JPanel top = new JPanel();        
    top.setLayout(new GridLayout(n, 2, 5, 5));
    Font police = new Font("Arial", Font.BOLD, 14);
    labels = new JLabel[n];
    jtfs = new JTextField[n];
    for(int i = 0 ; i < n ; i++) {
        labels[i] = new JLabel(man[i]);
        labels[i].setHorizontalAlignment(SwingConstants.RIGHT);
        jtfs[i] = new JTextField();
        jtfs[i].setFont(police);
        jtfs[i].setPreferredSize(new Dimension(200, 10));
        jtfs[i].setForeground(Color.BLUE);
        top.add(labels[i]);
        top.add(jtfs[i]);
    }
    b.addActionListener(new BoutonListener(request, client, window, this));
    container.add(top,BorderLayout.CENTER);
    container.add(b, BorderLayout.SOUTH);
    this.setContentPane(container);
    this.setVisible(true);            
  }       

  class BoutonListener extends AbstractAction{
	private String request;
	private Client client;
	private MainWindow window;
	private RequestWindow rwindow;
	
	public BoutonListener(String request, Client client, MainWindow window, RequestWindow rwindow) {
		super();
		this.request = request;
		this.client = client;
		this.window = window;
		this.rwindow = rwindow;
	}
    public void actionPerformed(ActionEvent e) {
        String tmpText;
        for(int i = 0 ; i < n ; i++) {
            tmpText = jtfs[i].getText();
            if(tmpText.equals("")) {
                tmpText = "null";
            }
            request = request + " " + tmpText;
        }
    	this.rwindow.dispose();
    	String response = client.send(request);
    	window.displayRequest(request);
	    if(response == "fail") {
	    		window.displayError("Fail, please check that you have correctly entered the request");
	    }
	    else {
            response = response;
	    		window.displayResponse(response);
	    }
    }
  }
}
