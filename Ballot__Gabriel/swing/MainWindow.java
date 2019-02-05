import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JToolBar;
import javax.swing.UIManager;

public class MainWindow extends JFrame{
	//Class version
	private static final long serialVersionUID = 1L;
	//Components of the main window
	private JButton button1 = new JButton(new AddTextListener("All Medias", this));
	private JButton button2 = new JButton(new CloseListener("Quit"));
	private JButton button3 = new JButton(new AddTextListener("All Groups", this));
	private JButton button4 = new JButton(new AddTextListener("All Medias", this));
	private JButton button5 = new JButton(new CloseListener("Quit"));
	private JButton button6 = new JButton(new AddTextListener("Play a Media", this));
	private JTextArea textarea = new JTextArea(20,30);
	private JScrollPane scroll = new JScrollPane(textarea);
	private JMenuBar menubar = new JMenuBar();
	private JMenu mainMenu = new JMenu("Menu");
	private JMenu createMenu = new JMenu("Create");
	private JMenu searchMenu = new JMenu("Search");
	private JMenu deleteMenu = new JMenu("Delete");
	private JToolBar toolbar = new JToolBar("Tool bar");
	
	private JMenuItem quitItem = new JMenuItem(new CloseListener("Quit"));
	private JMenuItem addMediaToGroupItem = new JMenuItem(new AddTextListener("Add a Media to a Group", this));
	private JMenuItem openMediaItem = new JMenuItem(new AddTextListener("Open a media", this));
	
	private JMenuItem createVideoItem = new JMenuItem(new AddTextListener("Video", this));
	private JMenuItem createPhotoItem = new JMenuItem(new AddTextListener("Photo", this));
	private JMenuItem createFilmItem = new JMenuItem(new AddTextListener("Film", this));
	private JMenuItem createGroupItem = new JMenuItem(new AddTextListener("Group", this));
	
	private JMenuItem searchMediaItem = new JMenuItem(new AddTextListener("Media", this));
	private JMenuItem searchGroupItem  = new JMenuItem(new AddTextListener("Group", this));
	private JMenuItem allMediaItem = new JMenuItem(new AddTextListener("All Medias", this));
	private JMenuItem allGroupItem = new JMenuItem(new AddTextListener("All Groups", this));
	
	private JMenuItem deleteMediaItem = new JMenuItem(new AddTextListener("Media", this));
	private JMenuItem deleteGroupItem  = new JMenuItem(new AddTextListener("Group", this));
	
	private Client client;
	
	public MainWindow(Client client) {
		this.client = client;
		//Disable Apple GUI look
		try {
		    UIManager.setLookAndFeel( UIManager.getCrossPlatformLookAndFeelClassName() );
		 } catch (Exception e) {
		            e.printStackTrace();
		 }
		System.setProperty("apple.laf.useScreenMenuBar", "true");
		
		//Design of buttons
		button1.setBackground(Color.blue);
		button1.setOpaque(true);
		button2.setBackground(Color.red);
		button2.setOpaque(true);
		button3.setBackground(Color.green);
		button3.setOpaque(true);

		//Menus Layout
		mainMenu.add(openMediaItem);
		mainMenu.add(addMediaToGroupItem);
		mainMenu.add(quitItem);
		
		createMenu.add(createPhotoItem);
		createMenu.add(createVideoItem);
		createMenu.add(createFilmItem);
		createMenu.add(createGroupItem);
		
		searchMenu.add(searchMediaItem);
		searchMenu.add(searchGroupItem);
		searchMenu.add(allMediaItem);
		searchMenu.add(allGroupItem);
		
		deleteMenu.add(deleteMediaItem);
		deleteMenu.add(deleteGroupItem);

		menubar.add(mainMenu);
		menubar.add(createMenu);
		menubar.add(searchMenu);
		menubar.add(deleteMenu);
		setJMenuBar(menubar);
		
		//ToolBar layout
		toolbar.add(button4);
		toolbar.add(button5);
		toolbar.add(button6);
		
		//BorderLayout
		JPanel buttonContainer = new JPanel();
		JPanel toolBarContainer = new JPanel();
		buttonContainer.setLayout(new GridLayout(1,3));
		buttonContainer.add(button1);
		buttonContainer.add(button2);
		buttonContainer.add(button3);
		toolBarContainer.add(toolbar);
		buttonContainer.setPreferredSize(new Dimension(30,30));
		add(scroll, BorderLayout.CENTER);
		add(buttonContainer, BorderLayout.SOUTH);
		add(toolBarContainer, BorderLayout.NORTH);
				
		//Display main window
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		pack();
		setVisible(true);			
	}
	
	public void displayRequest(String text) {
		textarea.setForeground(Color.red);
		textarea.append("* Request : " + text + "\n");
	}

	public void displayResponse(String text) {
		textarea.append("------------> Response : " + text + "\n");
	}
	
	public void displayError(String text) {
		textarea.setForeground(Color.red);
		textarea.append(text + "\n");
	}
	
	
	//Quit Button Listener
	class CloseListener extends AbstractAction {
		public CloseListener(String texte) {
			super(texte);
		}
		@Override
		public void actionPerformed(ActionEvent arg0) {
			// TODO Auto-generated method stub
			int n = JOptionPane.showConfirmDialog(null, "Are you sure you want to quit ?", "Quit", JOptionPane.YES_NO_OPTION);
			switch(n) {
			case 0 :
				System.exit(0);;
			case 1 :
			}
		}
	}
	
	//Communication protocol for client
	class AddTextListener extends AbstractAction {
		private MainWindow window;
		public AddTextListener(String texte, MainWindow window) {
			super(texte);
			this.window = window;
		}
		@Override
		public void actionPerformed(ActionEvent arg0) {
			String request = null;
			String man = null;
			//All Medias
			if (arg0.getSource() == button1 || arg0.getSource() == allMediaItem || arg0.getSource() == button4) {
				request = "get allmedias";
				window.displayRequest(request);
				String response = client.send(request);
			    if(response == "fail") {
			    		window.displayError("Fail");
			    }
			    else {
			    		window.displayResponse(response);
			    }	
			}
			//All Groups
			else if (arg0.getSource() == allGroupItem || arg0.getSource() == button3) {
				request = "get allgroups";
				window.displayRequest(request);
				String response = client.send(request);
			    if(response == "fail") {
			    		window.displayError("Fail");
			    }
			    else {
			    		window.displayResponse(response);
			    }
			}
			//Create a photo
			else if (arg0.getSource() == createPhotoItem) {
				request = "create photo ";
				man = "[<name> <path> <latitude> <longitude>]";
				new RequestWindow(request,man,client,window);
			}
			//Create a video
			else if (arg0.getSource() == createVideoItem) {
				request = "create video ";
				man = "[<name> <path> <length>]";
				new RequestWindow(request,man,client,window);
			}
			//Create a film
			else if (arg0.getSource() == createFilmItem) {
				request = "create film ";
				man = "[<name> <path> <length> [<nb_chapters> <tab>]]";
				new RequestWindow(request,man,client,window);
			}
			//Create a group
			else if (arg0.getSource() == createGroupItem) {
				request = "create group ";
				man = "[<name>]";
				new RequestWindow(request,man,client,window);
			}
			//Open a media
			else if (arg0.getSource() == openMediaItem || arg0.getSource() == button6) {
				request = "open ";
				man = "<name>";
				new RequestWindow(request,man,client,window);
			}
			//Search a media
			else if (arg0.getSource() == searchMediaItem) {
				request = "get media ";
				man = "<name>";
				new RequestWindow(request,man,client,window);
			}
			//Search a group
			else if (arg0.getSource() == searchGroupItem) {
				request = "get group ";
				man = "<name>";
				new RequestWindow(request,man,client,window);
			}
			//Delete a Media
			else if (arg0.getSource() == deleteMediaItem) {
				request = "delete media ";
				man = "<name>";
				new RequestWindow(request,man,client,window);
			}
			//Delete a Group
			else if (arg0.getSource() == deleteGroupItem) {
				request = "delete group ";
				man = "<name>";
				new RequestWindow(request,man,client,window);
			}
			//Add a media to a group
			else if (arg0.getSource() == addMediaToGroupItem) {
				request = "add ";
				man = "<group_name> <media_name>";
				new RequestWindow(request,man,client,window);
			}
			
		}
		
	}
	
}
