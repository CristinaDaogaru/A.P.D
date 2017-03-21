package inmultire;

import java.util.concurrent.LinkedBlockingQueue;
import inmultire.*;

public class ThreadPool {
	private final int nrThreaduri;

	private PoolWorker[] thread_uri;

	private static final LinkedBlockingQueue queue = new LinkedBlockingQueue();



	public static LinkedBlockingQueue getQueue() {
		return queue;
	}

	public ThreadPool(int nrThreaduri) {

		this.nrThreaduri = nrThreaduri;
		thread_uri = new PoolWorker[nrThreaduri];

		for (int i = 0; i < nrThreaduri; i++) {

			thread_uri[i] = new PoolWorker();

			thread_uri[i].start();

		}

	}

	
	public void execute(Runnable task) {

		synchronized (queue) {

			queue.add(task);

			queue.notify();
		}

	}
	
}