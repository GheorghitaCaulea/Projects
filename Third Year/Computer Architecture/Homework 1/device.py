"""
This module represents a device.

Computer Systems Architecture Course
Assignment 1
March 2018
"""

from threading import Event, Thread, Lock, Condition


class ReusableBarrierCond(object):
    """
    Class that represents a reusable barrier
    and is imported from the third lab.
    """
    def __init__(self, num_threads):
        """
        Constructor.

        @type num_threads: Integer
        @param num_threads: The number of threads for barrier

        @type count_threads: Integer
        @param count_threads: A variable that counts how
        many threads have arrieved at barrier

        @type cond: Condition
        @param cond: Does the synchronization
        """
        self.num_threads = num_threads
        self.count_threads = self.num_threads
        self.cond = Condition()

    def wait(self):
        """
        Wait method.
        """
        self.cond.acquire()
        self.count_threads -= 1
        if self.count_threads == 0:
            self.cond.notify_all()
            self.count_threads = self.num_threads
        else:
            self.cond.wait()
        self.cond.release()

class Device(object):
    """
    Class that represents a device.
    """

    def __init__(self, device_id, sensor_data, supervisor):
        """
        Constructor.

        @type device_id: Integer
        @param device_id: the unique id of this node; between 0 and N-1

        @type sensor_data: List of (Integer, Float)
        @param sensor_data: a list containing (location, data) as measured by this device

        @type supervisor: Supervisor
        @param supervisor: the testing infrastructure's control and validation component

        @type scripts: List of (script, Integer)
        @param scripts: a list containing (script, location)

        @type timepoint_done: Event
        @param timepoint_done: an event that let me know when it
        comes to another timepoint

        @type thread: DeviceThread
        @param thread: a thread which manage the work of MyThreads

        @type location_lock: Dictionary {Integer : Lock}
        @param location_lock: a dictionary which contains a lock foreach location

        @type barrier: ReusableBarrierCond
        @param barrier: a barrier which help me to synchronize the devices
        """

        self.device_id = device_id
        self.sensor_data = sensor_data
        self.supervisor = supervisor
        self.scripts = []
        self.timepoint_done = Event()
        self.thread = None
        self.location_lock = {}
        self.barrier = None

    def __str__(self):
        """
        Pretty prints this device.

        @rtype: String
        @return: a string containing the id of this device
        """

        return "Device %d" % self.device_id

    def setup_devices(self, devices):
        """
        Setup the devices before simulation begins.

        @type devices: List of Device
        @param devices: list containing all devices
        """
        # Create a list with all device_id.
        id_list = []
        for device in devices:
            id_list.append(device.device_id)
        # Find the smallest device_id.
        id_leader = min(id_list)

        # Only device with the smallest id will execute the following sequence.
        if self.device_id == id_leader:
            # Create a reusable barrier for synchronize devices.
            barrier = ReusableBarrierCond(len(devices))
            # Each device will share the same barrier.
            # Each device will have a DeviceThread which
            # will start more MyThread.
            for device in devices:
                device.barrier = barrier
                device.thread = DeviceThread(device)
                device.thread.start()
            # Create the dictionary {location:lock}.
            location_list = []
            location_dict = {}
            for device in devices:
                for location in device.sensor_data:
                    if location not in location_list:
                        location_list.append(location)
            for location in location_list:
                lock = Lock()
                location_dict[location] = lock
            # Each device will share the same dictionary.
            for device in devices:
                device.location_lock = location_dict

    def assign_script(self, script, location):
        """
        Provide a script for the device to execute.

        @type script: Script
        @param script: the script to execute from now on at each timepoint; None if the
            current timepoint has ended

        @type location: Integer
        @param location: the location for which the script is interested in
        """
        if script is not None:
            self.scripts.append((script, location))
        else:
            self.timepoint_done.set()

    def get_data(self, location):
        """
        Returns the pollution value this device has for the given location.

        @type location: Integer
        @param location: a location for which obtain the data

        @rtype: Float
        @return: the pollution value
        """

        return self.sensor_data[location] if location in self.sensor_data else None

    def set_data(self, location, data):
        """
        Sets the pollution value stored by this device for the given location.

        @type location: Integer
        @param location: a location for which to set the data

        @type data: Float
        @param data: the pollution value
        """

        if location in self.sensor_data:
            self.sensor_data[location] = data

    def shutdown(self):
        """
        Instructs the device to shutdown (terminate all threads). This method
        is invoked by the tester. This method must block until all the threads
        started by this device terminate.
        """
        self.thread.join()


class DeviceThread(Thread):
    """
    Class that implements the device's Master thread.
    """

    def __init__(self, device):
        """
        Constructor.

        @type device: Device
        @param device: the device which owns this Marster Thread
        """
        Thread.__init__(self, name="Device Thread %d" % device.device_id)
        self.device = device

    def run(self):

        while True:
            # Get the current neighbourhood.
            neighbours = self.device.supervisor.get_neighbours()

            if neighbours is None:
                break
            # Wait until device receive a None script.
            self.device.timepoint_done.wait()
            self.device.timepoint_done.clear()

            # Create a list of 8 Worker Threads(MyThread).
            threads = []
            for i in range(8):
                scripts_list = {}
                aux = i
                # Create a dictionary of {location : scripts} for each
                # Worker Thread.
                while aux < len(self.device.scripts):
                    (script, location) = self.device.scripts[aux]
                    scripts_list[location] = script
                    aux += 8
                thread = MyThread(self.device, scripts_list, neighbours)
                threads.append(thread)
            # Stats and wait the threads.
            for i in range(8):
                threads[i].start()
            for i in range(8):
                threads[i].join()
            # Wait until all device will arrieve here.
            self.device.barrier.wait()


class MyThread(Thread):
    """
    Class that implements the device's Worker thread.
    """

    def __init__(self, device, scripts_list, neighbours):
        """
        Constructor.

        @type device: Device
        @param device: the device which owns this Worker thread

        @type scripts_list: dictionary {Integer: script}
        @param scripts_list: a disctionary {location:script} which represents
        all scripts that worker thread must to resolve

        @type neighbours: List of Device
        @param neighbours: a list of all device in the neighbourhood
        """
        Thread.__init__(self, name="Device Thread %d" % device.device_id)
        self.device = device
        self.scripts_list = scripts_list
        self.neighbours = neighbours

    def run(self):
        # For each location from dictionary
        for location in self.scripts_list:
            script_data = []
            # Collect data from current neighbours
            # Make acquire for that location.
            self.device.location_lock[location].acquire()
            for dev in self.neighbours:
                data = dev.get_data(location)
                if data is not None:
                    script_data.append(data)
            # Add our data, if any.
            data = self.device.get_data(location)
            if data is not None:
                script_data.append(data)

            if script_data != []:
                # Run script on data.
                result = self.scripts_list[location].run(script_data)

                # Update data of neighbours.
                for dev in self.neighbours:
                    dev.set_data(location, result)
                # Update our data.
                self.device.set_data(location, result)
            # Make release for that location.
            self.device.location_lock[location].release()
