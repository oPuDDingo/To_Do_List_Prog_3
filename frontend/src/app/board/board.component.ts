import {Component, OnInit} from '@angular/core';
import {Board} from "../../lib/data-access/models/board";
import {List} from "../../lib/data-access/models/list";


@Component({
    selector: 'app-board',
    templateUrl: './board.component.html',
    styleUrls: ['./board.component.scss']
})
export class BoardComponent implements OnInit {

    board: Board;
    currentList?: List;
    flagged: List;
    today: List;
    showAddButton: boolean;


    constructor() {
    }

    ngOnInit(): void {
        this.board = {title: "My Board is the Load", lists: []};
        this.flagged = {title: "flagged", reminders: []};
        this.today = {title: "today", reminders: []};
        // this.dummyData();
        // this.currentList = this.board.lists[0];
    }

    // dummyData(): void {
    //     this.board = {"", [{1, "stuff", []}, {2, "stuff2", []}]};
    //     this.board = {title: "test",
    //         lists: [{id: 1, title: "stuff", reminders: [{id: 1, title: "r1", date: "31-12-2001"}, {id: 2, title: "r2", date: "31-12-2005"}]}, {
    //             id: 2,
    //             title: "stuff2",
    //             reminders: [{id: 1, title: "r1", date: "31-12-2002"}, {id: 2, title: "r2", date: "31-12-2003"}]
    //         }]
    //     };
    // }

    onListCardClicked(list: List){
        this.showAddButton = true;
        this.currentList = list;
    }

    onEditClicked(i: number, e: Event) {
        this.focusTitleInput(i)
        e.stopPropagation()
    }

    focusTitleInput(i: number) : void {
        document.getElementById("title-input" + i).removeAttribute("readonly");
        document.getElementById("title-input" + i).focus();
    }

    focusOutTitleInput(i : number) {
        document.getElementById("title-input"+i).setAttribute("readonly", "readonly");
    }

    onPlusClicked() {
        this.board.lists.push({id:1, title:"", reminders: []});
    }

    onDeleteClicked(list: List){
        let i: number = this.board.lists.indexOf(list);
        this.board.lists.splice(i, 1);
        if(this.currentList === list){
            this.currentList = undefined;
        }
    }

    onTodayClicked(){
        this.showAddButton = false;
        this.updateFilterLists();
        this.currentList = this.today;
    }

    onFlaggedClicked(){
        this.showAddButton = false;
        this.updateFilterLists();
        this.currentList = this.flagged;
    }

    updateFilterLists(){
        this.flagged.reminders.splice(0, this.flagged.reminders.length);
        this.today.reminders.splice(0, this.today.reminders.length);
        for(var i = 0; i < this.board.lists.length; i++) {
            for(var j = 0; j < this.board.lists[i].reminders.length; j++){
                if(this.board.lists[i].reminders[j].flagged === true){
                    this.flagged.reminders.push(this.board.lists[i].reminders[j]);
                }
                if(this.board.lists[i].reminders[j].date === new Date().toISOString().split('T')[0]){
                    this.today.reminders.push(this.board.lists[i].reminders[j]);
                }
            }
        }
    }

}
