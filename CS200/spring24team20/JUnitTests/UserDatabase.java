import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;

public class UserDatabase implements Serializable {
 
    ArrayList<User> users = new ArrayList<User>();

    public ArrayList<User> getUsers(){
        return users;
    }

    public boolean verifyUser(User u){
        User currentUser = new User();
        for(int i = 0; i < users.size(); i++){
            currentUser = users.get(i);
            if(currentUser.getID() == u.getID()){
                return true;
            }
        }
        return false;
    }

    public User getUser(int ID){
        User currentUser = new User();
        for(int i = 0; i < users.size(); i++){
            currentUser = users.get(i);
            if(currentUser.getID() == ID){
                return currentUser;
            }
        }
        return null;
    }

    public void addUser(User u){
        users.add(u);
    }

    public void removeUser(User u){
        users.remove(u);
    }

    public void updateUser(User oldUser, User newUser){
        int location = users.indexOf(oldUser);
        users.add(location, newUser);
        users.remove(oldUser);
    }

    public void writeToFile(String dirName) { //happens on Friday; persist all users currently in users and then clear users
        String fileName = "Users" + ".chocan";

        File logDir = new File(dirName);
        File outFile = new File(logDir.getAbsolutePath(), fileName);
        try{
            outFile.createNewFile();
            FileOutputStream outStream = new FileOutputStream(outFile);
            ObjectOutputStream obj_outStream = new ObjectOutputStream(outStream);
            obj_outStream.writeObject(this);
            obj_outStream.close();
            outStream.close();
        }
        catch (Exception except) {
            System.out.println(except.getMessage());
        }
    }
    public static UserDatabase readFromFile(String dirName, String fileName) {
        File logDir = new File(dirName);
        File inFile = new File(logDir.getAbsolutePath(), fileName);
        UserDatabase ret = new UserDatabase();
        try{
            FileInputStream inStream = new FileInputStream(inFile);
            ObjectInputStream obj_inStream = new ObjectInputStream(inStream);
            ret = (UserDatabase)obj_inStream.readObject();
            obj_inStream.close();
            return ret;
        }
        catch (Exception except) {
            System.out.println(except.getMessage());
        }
        return ret;
    }

}
