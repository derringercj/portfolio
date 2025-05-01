import java.util.*;
import java.util.concurrent.*;

public class Timer {

    //Calendar utilizes Datetime properties, which will be useful for timer.
    private Calendar timer = new GregorianCalendar(); 

    //Creating a thread that will be scheduled to a specific time.
    ScheduledExecutorService fridayMidnight = Executors.newSingleThreadScheduledExecutor();

    //Task that will be utilized within thread to print report.
    Runnable printReports = () -> {
        GenerateReport report;
        report = new GenerateReport();

        System.out.println("Printing reports...");

        report.allReports();
    };

    //Initially sets up variables before executing thread periodically.
    public void runReports()
    {
        final long NEXT_WEEK = 604800000;
        final long timeNow = System.currentTimeMillis();

        //This will reset timer to be set until an upcoming Friday.
        //If it is indeed Friday on the day of compilation, it will not matter
        //As the execution will still occur.
        timer.setTime(new Date());
        timer.set(Calendar.HOUR_OF_DAY, 0);
        timer.set(Calendar.MINUTE, 0);
        timer.set(Calendar.SECOND, 0);
        timer.set(Calendar.DAY_OF_WEEK, 1);

        //Depending on what the time is until Friday, that will be subtracted in milliseconds.
        final long startTime = timer.getTimeInMillis() - timeNow;

        //This will run the task printReports at the designated amount of milliseconds, then will
        //execute again next week in milliseconds forever and the rest of time (until this stops compiling).
        fridayMidnight.scheduleAtFixedRate(printReports, startTime, NEXT_WEEK, TimeUnit.MILLISECONDS);
    }
    
}
