import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.time.LocalDateTime;
import java.util.ArrayList;

public class ServiceDatabase implements Serializable {
    ArrayList<Service> serviceList;
    
    public ServiceDatabase() {
        serviceList = new ArrayList<Service>();
    }

    public void add(Service obj) {
        serviceList.add(obj);
    }
    
    public ArrayList<Service> search(Member mem) {      //list all services provided to a member this week
        ArrayList<Service> list = new ArrayList<Service>();
        for(Service it: serviceList) if(it.member.getID() == mem.getID()) list.add(it);
        return list;
    }
    public ArrayList<Service> search(Provider prov) {   //list all services provided by a provider this week
        ArrayList<Service> list = new ArrayList<Service>();
        for(Service it : serviceList) if(it.provider.getID() == prov.getID()) list.add(it);
        return list;
    }
    public ArrayList<Service> search(LocalDateTime date) {
        ArrayList<Service> list = new ArrayList<Service>();
        for(Service it : serviceList) if(it.dateTime == date) list.add(it);
        return list;
    }

    public void writeToFile(String dirName) { //happens on Friday; persist all services currently in serviceList and then clear serviceList
        String fileName = "Services" + ".chocan";

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
    public static ServiceDatabase readFromFile(String dirName, String fileName) {
        File logDir = new File(dirName);
        File inFile = new File(logDir.getAbsolutePath(), fileName);
        ServiceDatabase ret = new ServiceDatabase();
        try{
            FileInputStream inStream = new FileInputStream(inFile);
            ObjectInputStream obj_inStream = new ObjectInputStream(inStream);
            ret = (ServiceDatabase)obj_inStream.readObject();
            obj_inStream.close();
            inStream.close();
            return ret;
        }
        catch (Exception except) {
            System.out.println(except.getMessage());
        }
        return ret;
    }
}