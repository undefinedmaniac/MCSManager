import java.io.ByteArrayOutputStream;
import java.util.Arrays;

public class DynamicByteBuffer extends ByteArrayOutputStream {

    public void remove(int pos, int length) {
        if (pos < 0 || pos >= count)
            return;

        final int maxLength = count - pos;

        if (length <= 0 || length > maxLength)
            return;

        byte[] array;

        if (pos == 0) {
            array = right(count - length);
        } else if (pos + length == count) {
            array = left(count - length);
        } else {
            byte[] leftBytes = left(pos);
            byte[] rightBytes = mid(pos + length);
            array = new byte[leftBytes.length + rightBytes.length];
            System.arraycopy(leftBytes, 0, array, 0, leftBytes.length);
            System.arraycopy(rightBytes, 0, array, leftBytes.length, rightBytes.length);
        }

        buf = array;
        count = array.length;
    }

    public byte[] left (int length) {
        return mid(0, length);
    }

    public byte[] right (int length) {
        return mid(count - length, length);
    }

    public byte[] mid (int pos) {
        return mid(pos, -1);
    }

    public byte[] mid(int pos, int length) {
        if (pos < 0 || pos >= count)
            return null;

        if (length == -1) {
            length = count - pos;
        }

        final int maxLength = count - pos;

        if (length <= 0 || length > maxLength)
            return null;

        return Arrays.copyOfRange(buf, pos, length + pos);
    }

    public int indexOf(byte[] data) {
        return indexOf(data, 0);
    }

    public int indexOf(byte[] data, int startingPos) {
        if (startingPos < 0 || startingPos >= count || data.length > (count - startingPos))
            return -1;

        final int lastCheckablePos = count - data.length;

        for (int i = startingPos; i <= lastCheckablePos; i++) {
            if (checkForBytes(data, i))
                return i;
        }

        return -1;
    }

    private boolean checkForBytes(byte[] bytes, int startPos) {
        for (int i = 0; i < bytes.length; i++) {
            if (bytes[i] != buf[startPos + i])
                return false;
        }
        return true;
    }
}
