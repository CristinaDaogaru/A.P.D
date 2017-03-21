package inmultire;

import java.util.concurrent.LinkedBlockingQueue;

public class PoolWorker extends Thread{

	int nrThreduri;
	ThreadPool threadPool = new ThreadPool(nrThreduri);
	
	public void run() {
		
		Runnable task;
		LinkedBlockingQueue queue = threadPool.getQueue();
		while (true) {

			synchronized (queue) {

				while (queue.isEmpty()) {

					try {

						queue.wait();

					} catch (InterruptedException e) {

						System.out.println( e.getMessage());

					}

				}

				task = (Runnable) queue.poll();

			}

			try {

				task.run();

			} catch (RuntimeException e) {

				System.out.println( e.getMessage());

			}

		}

	}
}


