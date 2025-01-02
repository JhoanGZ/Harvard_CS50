import { create } from 'zustand';

const TOAST_TIMEOUT = 2500;

const useToastStore = create((set) => ({
    toasts: [],
    addToast: (toast) => {
        const id = Date.now();
        set((state) => ({
            toasts: [
                ...state.toasts,
                {
                ...toast,
                id,
                timestamp: Date.now(),
                },
            ],
            }));

        setTimeout(() => {
        set((state) => ({
            toasts: state.toasts.filter((t) => t.id !== id),
        }));
        }, TOAST_TIMEOUT);
    },
    removeToast: (id) => {
        set((state) => ({
        toasts: state.toasts.filter((t) => t.id !== id),
        }));
    },
}));

export function useToast() {
    const { toasts, addToast, removeToast } = useToastStore();

    return {
        toast: addToast,
        toasts,
        dismissToast: removeToast,
    };
}