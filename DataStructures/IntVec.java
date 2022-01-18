public class IntVec {

    // Make our own assertion because Java does not have a reliable assert.
    private static void assertion(boolean expression) {
        if (!expression) {
        	System.err.println("Assertion failed!");
        	new Exception().printStackTrace(System.err);
        	System.exit(1);
        }
    }

    // Vector class internals begin here.
    private int[] _data;
    private int _size;
    
    public IntVec() {
    	_data = new int[2];
    	_size = 0;
    }

    /**
        Append an element to the end of this vector.
     */
    public void append(int val) {
    	if (_size == _data.length) {
    		int[] temp = _data;
    		_data = new int[_data.length * 2];
    		for (int x : temp) {
    			_data[x] = x;
    		}
    		
    	}
    	_data[_size] = val;
    	_size += 1;
        return;
    }

    /**
        Pop the element at the end of this vector.
     */
    public int pop() {
        return 0;
    }

    /**
        Remove an element at a given index in this vector.
     */
    public int remove(int idx) {
        return 0;
    }

    /**
        Insert an element into this vector at a given index.
     */
    public void insert(int val, int idx) {
    	//.(val, idx);
        return;
    }

    /**
        Returns true if this vector contains a given element.
     */
    public boolean contains(int val) {
    	for (int x : _data) {
    		if (x == val) {
    			return true;
    		} else {
    			return false;
    		}
    	}
		return false;
    }

    /**
        Return how many elements are in this vector.
     */
    public int size() {
        return _size;
    }

    /**
        Returns true if this vector contains no elements.
     */
    public boolean isEmpty() {
        return false;
    }

    /**
        Reverse the contents of this vector in place.
     */
    public void reverse() {
        return;
    }

    /**
        Sort the contents of this vector in place.
     */
    public void sort() {
        return;
    }

    /**
        Convert the contents of this vector to a new array.
        If the vector is empty, returns null.
     */
    public int[] toArray() {
        return null;
    }

    /**
        Convert the contents of this vector to a string.
     */
    public String toString() {
        return "";
    }

    public static void main(String[] args) {
        IntVec vec = new IntVec();
        for (int i = 0; i < 8; i++) vec.append(i);
        System.out.println(vec);
        System.out.println(vec.size());
        assertion(vec.size() == 8);
        assertion(vec.toString().equals("{0, 1, 2, 3, 4, 5, 6, 7}"));
        while (!vec.isEmpty()) {
            int val = vec.pop();
            assertion(val == vec.size());
        }
        assertion(vec.size() == 0);
        for (int i = 0; i < 8; i++) {
            vec.insert(0, i);
        }
        assertion(vec.toString().equals("{7, 6, 5, 4, 3, 2, 1, 0}"));
        assertion(vec.size() == 8);
        vec.sort();
        assertion(vec.toString().equals("{0, 1, 2, 3, 4, 5, 6, 7}"));
        assertion(vec.size() == 8);
        vec.reverse();
        assertion(vec.toString().equals("{7, 6, 5, 4, 3, 2, 1, 0}"));
        assertion(vec.size() == 8);
        int[] arr = vec.toArray();
        assertion(arr.length == vec.size() && arr.length == 8);
        for (int i = 0; i < arr.length; i++) {
            int val = arr[i];
            assertion(vec.contains(val));
            int removedFirst = vec.remove(0);
            assertion(removedFirst == val);
            vec.append(removedFirst);
        }
        assertion(vec.size() == 8);
        String out = vec.toString();
        assertion(out.equals("{0, 1, 2, 3, 4, 5, 6, 7}"));
        vec.reverse();
        assertion(vec.size() == 8);
        vec.sort();
        assertion(vec.size() == 8);
        assertion(vec.toString().equals(out));
    }
}
