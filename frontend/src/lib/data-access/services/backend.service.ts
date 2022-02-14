import {Injectable} from "@angular/core";
import {HttpClient} from "@angular/common/http";
import {Observable} from "rxjs";
import {Board} from "../models/board";
import {List} from "../models/list";
import {Reminder} from "../models/reminder";


@Injectable({
    providedIn: "root",
})
export class BackendService {
    readonly url: string = "http://localhost:4200";

    constructor(private client: HttpClient) {
    }

    loadBoard(): Observable<Board> {
        return this.client.get<Board>(this.url + "/api/board");
    }

    createList(list: Partial<List>): Observable<List> {
        let listPayload = {
            ...list,
        };
        return this.client.post<List>(this.url + "/api/board/lists", listPayload);
    }

    deleteList(listId: number) : Observable<void> {
        return this.client.delete<void>(this.url + "/api/board/lists/" + listId);
    }

    updateList(list: Partial<List>) : Observable<List> {
        let listPayload = {
            ...list,
        };
        return this.client.post<List>(this.url + "/api/board/lists/" + list.id, listPayload);
    }

    createReminder(listId : number, reminder: Partial<Reminder>) : Observable<Reminder> {
        let reminderPayload = {
            ...reminder,
        };
        return this.client.post<Reminder>(this.url + "/api/board/lists/" + listId + "/reminders", reminderPayload);
    }

    deleteReminder(listId: number, reminderId: number) : Observable<void>{
        return this.client.delete<void>(this.url + "/api/board/lists/" + listId + "/reminders/" + reminderId);
    }

    updateReminder(listId: number, reminderId: number, reminder: Partial<Reminder>): Observable<Reminder> {
        let reminderPayload = {
            ...reminder,
        };

        return this.client.put<Reminder>(this.url + "/api/board/lists/" + listId + "/reminders/" + reminderId, reminderPayload);
    }

}