import java.io.Serializable;
import java.time.LocalDateTime;

public class Service implements Serializable {
    public Provider provider;
    public Member member;
    public int code;
    public LocalDateTime dateTime;
    public String comments;
    public int fee;

    public Service(Provider param_provider, Member param_member, int param_code, LocalDateTime param_dateTime) {
        provider = param_provider;
        member = param_member;
        code = param_code;
        dateTime = param_dateTime;
    }

    public Service(Provider param_provider, Member param_member, int param_code, LocalDateTime param_dateTime, String param_comments) {
        provider = param_provider;
        member = param_member;
        code = param_code;
        dateTime = param_dateTime;
        comments = param_comments;
    }

    public void print() {
        System.out.println(dateTime.getMonthValue() + "-" + dateTime.getDayOfMonth() + "-" + dateTime.getYear() + " " + dateTime.getHour() + ":" + dateTime.getMinute() + ":" + dateTime.getSecond() + "\n");
    }

    public void setFee(int param_fee) {fee = param_fee;}
}