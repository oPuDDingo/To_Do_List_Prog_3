import { Reminder } from './reminder';

export interface List{
    id?: number;
    title: string;
    reminders: Reminder[];
}