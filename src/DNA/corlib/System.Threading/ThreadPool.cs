namespace System.Threading {
    public static class ThreadPool {
        public static bool QueueUserWorkItem(WaitCallback callBack) {
            return QueueUserWorkItem(callBack, null);
        }

        public static bool QueueUserWorkItem(WaitCallback callBack, object state) {
            if (callBack == null) {
                throw new ArgumentNullException("callBack");
            }

            var thread = new Thread(new ParameterizedThreadStart(InvokeCallback));
            thread.IsBackground = true;
            thread.Start(new WorkItem(callBack, state));
            return true;
        }

        private static void InvokeCallback(object workItemObj) {
            var workItem = (WorkItem)workItemObj;
            workItem.CallBack(workItem.State);
        }

        private sealed class WorkItem {
            public readonly WaitCallback CallBack;
            public readonly object State;

            public WorkItem(WaitCallback callBack, object state) {
                this.CallBack = callBack;
                this.State = state;
            }
        }
    }
}
