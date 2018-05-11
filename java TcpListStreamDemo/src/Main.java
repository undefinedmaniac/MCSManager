import java.nio.charset.StandardCharsets;

public class Main {
    public static void main(String[] args) {
        DynamicByteBuffer buffer = new DynamicByteBuffer();

        String test = "test";

        byte[] bytes = test.getBytes(StandardCharsets.UTF_8);

        try {
            buffer.write(bytes);
            buffer.write(bytes);
        } catch (Exception e) {
            e.printStackTrace();
        }

        buffer.remove(2, 4);

        System.out.println(buffer);
    }
}
