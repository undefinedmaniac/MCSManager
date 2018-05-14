public interface IBasicIODeviceListener {
    void readyRead();
    void error(Exception e);
}
